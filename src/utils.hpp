#pragma once

#include <chrono>

inline int64_t toTimestampMs(const std::chrono::system_clock::time_point& tp) {
	return std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch()).count();
}

inline std::chrono::system_clock::time_point fromTimestampMs(int64_t ms) {
	return std::chrono::system_clock::time_point(std::chrono::milliseconds(ms));
}

