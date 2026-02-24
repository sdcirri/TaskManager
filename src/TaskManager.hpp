#pragma once

#include <functional>
#include <optional>
#include <vector>

#include <nlohmann/json.hpp>

#include "Task.hpp"

using json = nlohmann::json;
using std::chrono::system_clock;
using std::chrono::time_point;
using std::reference_wrapper;
using std::shared_ptr;
using std::optional;
using std::vector;

class TaskManager {
	private:
		static inline uint64_t taskCounter = 0;
		vector<shared_ptr<Task>> tasks;

		TaskManager();
		optional<size_t> getTaskIdxById(uint64_t taskId) const;
	public:
		TaskManager(const TaskManager&) = delete;
		TaskManager& operator=(const TaskManager&) = delete;

		static TaskManager& getInstance();

		vector<shared_ptr<Task>> getTasks() const;
		optional<reference_wrapper<Task>> getTaskById(uint64_t taskId) const;
		uint64_t addTask(const string& title, const string& description, const time_point<system_clock>& expiresAt);
		bool deleteTask(uint64_t taskId);
		bool markTaskAsDone(uint64_t taskId) const;

		void tasksFromJson(json& j);
		void tasksFromJsonFile(const string& filename);
		void tasksToJson(json& j) const;
		void tasksToJsonFile(const string& filename) const;
};

