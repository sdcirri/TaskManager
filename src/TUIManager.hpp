#pragma once

#include <chrono>

using namespace std::chrono;

class TUIManager {
	private:
		TUIManager();
		static std::string getline();
		static time_point<system_clock> inputDateTime();
	public:
		TUIManager(const TUIManager&) = delete;
		TUIManager& operator=(const TUIManager&) = delete;

		static TUIManager& getInstance();

		static void listTasks();
		static void addTask();
		static uint64_t selectTask();
		static void manageTask(uint64_t taskId);
		static void clrscr();
		static void uiLoop();
};

