#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <optional>
#include <vector>
#include <chrono>

#include "TaskManager.hpp"

using namespace std::chrono;

using std::optional;
using std::string;
using std::vector;

TEST_CASE("Singleton TaskManager") {
	auto& p1 = TaskManager::getInstance();
	auto& p2 = TaskManager::getInstance();
	REQUIRE(&p1 == &p2);
}

TEST_CASE("Storage tasks") {
	auto now = system_clock::now();
	auto& tm = TaskManager::getInstance();

	vector<string> taskNames = {
		"Raccolta requisiti",
		"Analisi requisiti",
		"Modello use-case",
		"Specifiche use-case",
		"Modello di analisi",
		"Modello di design",
		"Implementazione e test unitari",
		"Test di integrazione",
		"Test funzionali",
		"Deployment"
	};
	vector<uint64_t> daysFromNow = {1, 10, 20, 50, 100, 150, 250, 300, 350, 400};
	vector<uint64_t> taskIds;

	for(auto i = 0; i < taskNames.size(); i++)
		taskIds.push_back( tm.addTask(taskNames[i], "", now + days{daysFromNow[i]}) );

	for(auto i = 0; i < taskIds.size(); i++) {
		auto to = tm.getTaskById(taskIds[i]);
		REQUIRE(to.has_value());
		Task t = to->get();
		REQUIRE(t.getTitle() == taskNames[i]);
		REQUIRE(tm.markTaskAsDone(taskIds[i]) == true);
		REQUIRE(tm.deleteTask(taskIds[i]) == true);
	}
}

TEST_CASE("Storage JSON") {
	const string filename = "/tmp/tasks.json";
	auto now = system_clock::now();
	auto& tm = TaskManager::getInstance();

	vector<string> taskNames = {
		"Raccolta requisiti",
		"Analisi requisiti",
		"Modello use-case",
		"Specifiche use-case",
		"Modello di analisi",
		"Modello di design",
		"Implementazione e test unitari",
		"Test di integrazione",
		"Test funzionali",
		"Deployment"
	};
	vector<uint64_t> daysFromNow = {1, 10, 20, 50, 100, 150, 250, 300, 350, 400};
	vector<uint64_t> taskIds;

	for(auto i = 0; i < taskNames.size(); i++)
		taskIds.push_back( tm.addTask(taskNames[i], "", now + days{daysFromNow[i]}) );

	tm.tasksToJsonFile(filename);
	for(auto taskId : taskIds)
		tm.deleteTask(taskId);
	tm.tasksFromJsonFile(filename);

	for(auto i = 0; i < taskIds.size(); i++) {
		auto to = tm.getTaskById(taskIds[i]);
		REQUIRE(to.has_value());
		Task t = to->get();
		REQUIRE(t.getTitle() == taskNames[i]);
		REQUIRE(tm.markTaskAsDone(taskIds[i]) == true);
		REQUIRE(tm.deleteTask(taskIds[i]) == true);
	}
}

TEST_CASE("Shallow copy tasks") {
	auto& tm = TaskManager::getInstance();
	auto exp = system_clock::now() + days(10);
	tm.addTask("Studiare gestione memoria in C++", "Difficile", exp);

	string newDesc = "Molto difficile";
	auto tasks = tm.getTasks();
	auto& task = tasks.at(0);
	uint64_t tId = task->getId();

	task->setDescription(string(newDesc));
	auto to = tm.getTaskById(tId);
	REQUIRE(to.has_value());
	REQUIRE(to->get().getDescription() == newDesc);
}
