#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <chrono>

#include "Task.hpp"
#include "utils.hpp"

using namespace std::chrono;
using std::string;

TEST_CASE("Un task viene inizializzato correttamente") {
	auto in10Days = system_clock::now() + days{10};
	Task t(1, "Scrivi test unitari", "I test unitari sono molto importanti", in10Days);
	REQUIRE(t.getId() == 1);
	REQUIRE(t.getTitle() == "Scrivi test unitari");
	REQUIRE(t.getDescription() == "I test unitari sono molto importanti");
	REQUIRE(toTimestampMs(t.getExpiresAt()) - toTimestampMs(in10Days) == 0);
	REQUIRE(t.isDone() == false);
}

TEST_CASE("Un task viene flaggato come completato correttamente") {
	auto in10Days = system_clock::now() + days{10};
	Task t(1, "Scrivi test unitari", "I test unitari sono molto importanti", in10Days);
	t.markAsDone();
	REQUIRE(t.isDone() == true);
}

TEST_CASE("Deserializzazione JSON task") {
	auto in10Days = system_clock::now() + days{10};
	json j;
	j["id"] = 5;
	j["title"] = "Scrivi test unitari";
	j["description"] = "I test unitari sono molto importanti";
	j["expires_at"] = toTimestampMs(in10Days);
	j["done"] = false;
	Task t(j);

	REQUIRE(t.getId() == 5);
	REQUIRE(t.getTitle() == "Scrivi test unitari");
	REQUIRE(t.getDescription() == "I test unitari sono molto importanti");
	REQUIRE(toTimestampMs(t.getExpiresAt()) - toTimestampMs(in10Days) == 0);
	REQUIRE(t.isDone() == false);
}

TEST_CASE("Serializzazione JSON task") {
	auto in10Days = system_clock::now() + days{10};
	Task t(2, "Scrivi test unitari", "I test unitari sono molto importanti", in10Days);
	json j;
	t.asJson(j);

	auto expiresAt = fromTimestampMs(j.at("expires_at").get<int64_t>());

	REQUIRE(j.at("id").get<uint64_t>() == 2);
	REQUIRE(j.at("title").get<string>() == "Scrivi test unitari");
	REQUIRE(j.at("description").get<string>() == "I test unitari sono molto importanti");
	REQUIRE(toTimestampMs(expiresAt) - toTimestampMs(in10Days) == 0);
	REQUIRE(j.at("done").get<bool>() == false);
}

