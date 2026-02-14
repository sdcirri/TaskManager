#pragma once

#include <functional>
#include <optional>
#include <vector>

#include "json.hpp"
#include "Task.hpp"

using json = nlohmann::json;
using std::reference_wrapper;
using std::optional;
using std::vector;

class TaskManager {
	private:
		static inline uint64_t taskCounter = 0;
		vector<Task> tasks;

		TaskManager();
		optional<size_t> getTaskIdxById(uint64_t taskId) const;
	public:
		TaskManager(const TaskManager&) = delete;
		TaskManager& operator=(const TaskManager&) = delete;

		static TaskManager& getInstance();

		vector<Task> getTasks() const;
		optional<reference_wrapper<Task>> getTaskById(uint64_t taskId);
		uint64_t addTask(string title, string description, time_point<system_clock> expiresAt);
		bool deleteTask(uint64_t taskId);
		bool markTaskAsDone(uint64_t taskId);

		void tasksFromJson(json& j);
		void tasksFromJsonFile(const string& filename);
		void tasksToJson(json& j);
		void tasksToJsonFile(const string& filename);
};

