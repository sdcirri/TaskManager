#include <functional>
#include <algorithm>
#include <optional>
#include <fstream>
#include <vector>

#include "TaskManager.hpp"
#include "Task.hpp"
#include "json.hpp"
#include "utils.hpp"

using json = nlohmann::json;
using std::reference_wrapper;
using std::optional;
using std::ifstream;
using std::ofstream;
using std::nullopt;
using std::vector;
using std::ref;
using std::max;

TaskManager::TaskManager() {}

TaskManager& TaskManager::getInstance() {
	static TaskManager instance;
	return instance;
}

optional<size_t> TaskManager::getTaskIdxById(uint64_t taskId) const {
	for(auto i = 0; i < tasks.size(); i++)
		if(tasks.at(i).getId() == taskId)
			return i;
	return nullopt;
}

optional<reference_wrapper<Task>> TaskManager::getTaskById(uint64_t taskId) {
	optional<size_t> idx = this->getTaskIdxById(taskId);
	if(idx.has_value())	return ref(tasks.at(*idx));
	return nullopt;
}

vector<Task> TaskManager::getTasks() const {
	return tasks;
}

uint64_t TaskManager::addTask(string title, string description, time_point<system_clock> expiresAt) {
	Task t(taskCounter++, title, description, expiresAt);
	tasks.push_back(t);
	return t.getId();
}

bool TaskManager::deleteTask(uint64_t taskId) {
	optional<size_t> idx = this->getTaskIdxById(taskId);
	if(!idx.has_value())	return false;
	tasks.erase(tasks.begin() + *idx);
	return true;
}

bool TaskManager::markTaskAsDone(uint64_t taskId) {
	auto t = this->getTaskById(taskId);
	if(!t)	return false;
	t->get().markAsDone();
	return true;
}

void TaskManager::tasksFromJson(json& j) {
	if(!tasks.empty())	tasks.clear();
	for(const auto& jtask : j) {
		Task task(jtask);
		tasks.push_back(task);
		taskCounter = max(taskCounter, task.getId());
	}
}

void TaskManager::tasksFromJsonFile(const string& filename) {
	ifstream ifile(filename);
	json j;
	ifile >> j;
	tasksFromJson(j);
}

void TaskManager::tasksToJson(json& j) {
	j = json::array();
	for(Task task : tasks) {
		json jtask;
		task.asJson(jtask);
		j.push_back(jtask);
	}
}

void TaskManager::tasksToJsonFile(const string& filename) {
	ofstream ofile(filename);
	json j;
	tasksToJson(j);
	ofile << j;
}

