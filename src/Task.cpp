#include "Task.hpp"

#include <chrono>
#include <string>

#include <nlohmann/json.hpp>

#include "utils.hpp"

using json = nlohmann::json;
using namespace std::chrono;
using std::string;

Task::Task(uint64_t id, const string& title, const string& description, const time_point<system_clock>& expiresAt) :
	id(id),
	title(title),
	description(description),
	expiresAt(expiresAt),
	done(false) {}

Task::Task(const json& j) {
	j.at("id").get_to(this->id);
	j.at("title").get_to(this->title);
	j.at("description").get_to(this->description);
	this->expiresAt = fromTimestampMs(j.at("expires_at").get<int64_t>());
	j.at("done").get_to(this->done);
}

uint64_t Task::getId() const {
	return id;
}

string Task::getTitle() const {
	return title;
}

string Task::getDescription() const {
	return description;
}

time_point<system_clock> Task::getExpiresAt() const {
	return expiresAt;
}

bool Task::isDone() const {
	return done;
}

void Task::setTitle(const string& title) {
	this->title = title;
}

void Task::setDescription(const string& description) {
	this->description = description;
}

void Task::setExpiresAt(const time_point<system_clock>& expiresAt) {
	this->expiresAt = expiresAt;
}

void Task::markAsDone() {
	done = true;
}

void Task::asJson(json& j) {
	j = {
		{"id", this->id},
		{"title", this->title},
		{"description", this->description},
		{"expires_at", toTimestampMs(this->expiresAt)},
		{"done", this->done}
	};
}

