CC = clang++
CCFLAGS = -I./src -std=c++20
TESTFLAGS = -lCatch2Main -lCatch2

test_task: tests/test_task.cpp src/Task.hpp src/Task.cpp src/json.hpp src/utils.hpp
	$(CC) $(CCFLAGS) tests/test_task.cpp src/Task.cpp -o tests/test_task $(TESTFLAGS) && ./tests/test_task && rm ./tests/test_task

test_task_manager: tests/test_task_manager.cpp src/Task.hpp src/Task.cpp src/TaskManager.hpp src/TaskManager.cpp src/json.hpp src/utils.hpp
	$(CC) $(CCFLAGS) tests/test_task_manager.cpp src/Task.cpp src/TaskManager.cpp -o tests/test_task_manager $(TESTFLAGS) && ./tests/test_task_manager && rm ./tests/test_task_manager

unit_tests: test_task test_task_manager

