#include "TaskManager.hpp"

#include <algorithm>
#include <fstream>
#include <functional>
#include <optional>
#include <vector>

#include <nlohmann/json.hpp>

#include "Task.hpp"
#include "utils.hpp"

using json = nlohmann::json;
using namespace std;

TaskManager::TaskManager() {}

TaskManager& TaskManager::getInstance() {
	static TaskManager instance;
	return instance;
}

optional<size_t> TaskManager::getTaskIdxById(uint64_t taskId) const {
	for(auto i = 0; i < tasks.size(); i++)
		if(tasks.at(i)->getId() == taskId)
			return i;
	return nullopt;
}

optional<reference_wrapper<Task>> TaskManager::getTaskById(const uint64_t taskId) const {
	if(const optional<size_t> idx = this->getTaskIdxById(taskId); idx.has_value())
		return ref(*tasks.at(*idx));
	return nullopt;
}

vector<shared_ptr<Task>> TaskManager::getTasks() const {
	return tasks;
}

uint64_t TaskManager::addTask(const string& title, const string& description, const time_point<system_clock>& expiresAt) {
	Task t(taskCounter++, title, description, expiresAt);
	tasks.push_back(make_shared<Task>(t));
	return t.getId();
}

bool TaskManager::deleteTask(const uint64_t taskId) {
	const optional<size_t> idx = this->getTaskIdxById(taskId);
	if(!idx.has_value())	return false;
	tasks.erase(tasks.begin() + *idx);
	return true;
}

bool TaskManager::markTaskAsDone(const uint64_t taskId) const {
	const auto t = this->getTaskById(taskId);
	if(!t)	return false;
	t->get().markAsDone();
	return true;
}

void TaskManager::tasksFromJson(json& j) {
	if(!tasks.empty())	tasks.clear();
	for(const auto& jtask : j) {
		Task task(jtask);
		tasks.push_back(make_shared<Task>(task));
		taskCounter = max(taskCounter, task.getId()+1);
	}
}

void TaskManager::tasksFromJsonFile(const string& filename) {
	ifstream ifile(filename);
	json j;
	ifile >> j;
	tasksFromJson(j);
}

void TaskManager::tasksToJson(json& j) const {
	j = json::array();
	for(auto& task : tasks) {
		json jtask;
		task->asJson(jtask);
		j.push_back(jtask);
	}
}

void TaskManager::tasksToJsonFile(const string& filename) const {
	ofstream ofile(filename);
	json j;
	tasksToJson(j);
	ofile << j;
}

