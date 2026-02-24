#include <filesystem>
#include <string>

#include <pwd.h>
#include <unistd.h>

#include "TaskManager.hpp"
#include "TUIManager.hpp"

#define STORAGE_USR_RELPATH ".local/share/task_manager"
#define STORAGE_FILENAME "tasks.json"

namespace fs = std::filesystem;
using std::string;

string initStorage();

int main() {
	const string storageFile = initStorage();
	TaskManager& tm = TaskManager::getInstance();

	try {
		tm.tasksFromJsonFile(storageFile);
	}
	catch(nlohmann::detail::parse_error) {}

	TUIManager::uiLoop();
	tm.tasksToJsonFile(storageFile);
	return 0;
}

string initStorage() {
	const string home = getpwuid(getuid())->pw_dir;
	const fs::path storageFile = fs::path(home) / STORAGE_USR_RELPATH / STORAGE_FILENAME;
	fs::create_directories(storageFile.parent_path());
	return storageFile.string();
}

