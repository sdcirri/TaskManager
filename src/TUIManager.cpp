#include "TUIManager.hpp"

#include <chrono>
#include <format>
#include <iostream>

#include "TaskManager.hpp"

using namespace std::chrono;
using namespace std;

TUIManager::TUIManager() = default;

time_point<system_clock> TUIManager::inputDateTime() {
	sys_days date;
	minutes time;
	string buf;

	while(true) {
		cout << "Data scadenza (AAAA-MM-GG): ";
		buf = getline();
		istringstream ds(buf);
		ds >> parse("%Y-%m-%d", date);
		if(!ds.fail()) break;
	}
	while(true) {
		cout << "Ora scadenza (HH:MM:SS): ";
		buf = getline();
		istringstream ts(buf);
		ts >> parse("%H:%M:%S", time);
		if(!ts.fail()) break;
	}

	const time_point<system_clock> expiresAt = date + time;
	return expiresAt;
}

string TUIManager::getline() {
	string buf;
	if(!std::getline(cin, buf)) throw ios_base::failure("EOF");
	return buf;
}

TUIManager& TUIManager::getInstance() {
	static TUIManager instance;
	return instance;
}

void TUIManager::listTasks() {
	for(const auto& tm = TaskManager::getInstance(); const auto& task : tm.getTasks()) {
		string description = task->getDescription();
		const bool overdue = system_clock::now() >= task->getExpiresAt();
		cout << "----------------------------------------------------" << endl;
		cout << (task->isDone() ? "[V] " : (overdue ? "[!] " : "[ ] "));
		cout << "Task \"" << task->getTitle() << "\" (ID: " << task->getId() << ")" << endl;
		cout <<  (!description.empty() ? "\t" + description + "\n" : "");
		cout << "Scadenza: " << format("{:%Y-%m-%d %H:%M:%S}", task->getExpiresAt()) << (overdue ? "!" : "") << endl;
	}
}

void TUIManager::addTask() {
	auto& tm = TaskManager::getInstance();

	cout << "-- Nuova attività --" << endl;
	cout << "Titolo: ";
	const string title = getline();
	cout << "Descrizione (opz.): ";
	const string description = getline();

	const time_point<system_clock> expiresAt = inputDateTime();
	tm.addTask(title, description, expiresAt);
	cout << "Task creato con successo." << endl;
}

uint64_t TUIManager::selectTask() {
	const auto& tm = TaskManager::getInstance();
	uint64_t sel;
	string buf;

	listTasks();

	while(true) {
		cout << "Seleziona un'attività da gestire (ID): ";
		buf = getline();
		auto [ptr, ec] = from_chars(buf.data(), buf.data() + buf.size(), sel);
		if(ec == errc() && ptr == buf.data() + buf.size()) {
			if(tm.getTaskById(sel).has_value()) break;
		}
		cout << "Input non valido, riprova" << endl;
	}
	return sel;
}

void TUIManager::manageTask(const uint64_t taskId) {
	auto& tm = TaskManager::getInstance();
	auto& task = tm.getTaskById(taskId)->get();

	cout << "Task \"" << task.getTitle() << "\" (ID: " << task.getId() << ")" << endl;
	cout << "1. Contrassegna come completato" << endl;
	cout << "  2. Modifica titolo" << endl;
	cout << "    3. Modifica descrizione" << endl;
	cout << "      4. Modifica scadenza" << endl;
	cout << "        5. Elimina task" << endl;

	while(true) {
		cout << " → ";
		string opt = getline();
		if(opt.empty()) continue;
		switch(opt.at(0)) {
			case '1':
				task.markAsDone();
				break;
			case '2': {
				cout << "Nuovo titolo: ";
				const string newTitle = getline();
				task.setTitle(newTitle);
				break;
			}
			case '3': {
				cout << "Nuova descrizione: ";
				const string newDescription = getline();
				task.setDescription(newDescription);
				break;
			}
			case '4': {
				const time_point<system_clock> newExpiresAt = inputDateTime();
				task.setExpiresAt(newExpiresAt);
				break;
			}
			case '5': {
				cout << "Sei sicuro? L'operazione è irreversibile! [s/N] ";
				if(const string conf = getline(); conf == "s" || conf == "S")
					tm.deleteTask(taskId);
				else cout << "Annullato." << endl;
				break;
			}
			default:
				break;
		}
		break;
	}
}

void TUIManager::clrscr() {
	for(auto i = 0; i < 255; i++) cout << endl;
}

void TUIManager::uiLoop() {
	while(true) {
		try {
			clrscr();
			listTasks();
			cout << "1. Nuova attività" << endl;
			cout << "  2. Gestisci attività" << endl;
			cout << "    3. Esci" << endl;
			while(true) {
				cout << " → ";
				const string opt = getline();
				if (opt.empty()) continue;
				switch(opt.at(0)) {
					case '1':
						addTask();
						break;
					case '2': {
						const uint64_t currentTask = selectTask();
						manageTask(currentTask);
						break;
					}
					case '3':
						return;
					default:
						break;
				}
				break;
			}
		}
		catch (const std::ios_base::failure& _) {
			return;
		}
	}
}

