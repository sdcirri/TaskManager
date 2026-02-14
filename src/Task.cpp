#include <utility>
#include <string>
#include <chrono>

#include "Task.hpp"
#include "utils.hpp"
#include "json.hpp"

using json = nlohmann::json;
using namespace std::chrono;
using std::string;

Task::Task(uint64_t id, string title, string description, time_point<system_clock> expiresAt) :
	id(id),
	title(std::move(title)),
	description(std::move(description)),
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

void Task::setTitle(string& title) {
	this->title = std::move(title);
}

void Task::setDescription(string& description) {
	this->description = std::move(description);
}

void Task::setExpiresAt(time_point<system_clock>& expiresAt) {
	this->expiresAt = std::move(expiresAt);
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

