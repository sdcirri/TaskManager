#pragma once

#include <chrono>

using namespace std::chrono;

inline int64_t toTimestampMs(const system_clock::time_point& tp) {
	return duration_cast<milliseconds>(tp.time_since_epoch()).count();
}

inline system_clock::time_point fromTimestampMs(const int64_t ms) {
	return system_clock::time_point(milliseconds(ms));
}

