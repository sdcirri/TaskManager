#pragma once

#include <string>
#include <chrono>

#include "json.hpp"

using json = nlohmann::json;
using namespace std::chrono;
using std::string;

class Task {
	private:
		uint64_t id;
		string title;
		string description;
		time_point<system_clock> expiresAt;
		bool done;
	public:
		Task(uint64_t id, string title, string description, time_point<system_clock> expiresAt);
		Task(const json& j);
		uint64_t getId() const;
		string getTitle() const;
		string getDescription() const;
		time_point<system_clock> getExpiresAt() const;
		bool isDone() const;

		void setTitle(string& title);
		void setDescription(string& description);
		void setExpiresAt(time_point<system_clock>& expiresAt);
		void markAsDone();

		void asJson(json& j);
};

