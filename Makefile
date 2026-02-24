CC = clang++
CCFLAGS = -I./src -std=c++20
TESTFLAGS = -lCatch2Main -lCatch2

.PHONY: all clean unit_tests test_task test_task_manager

all: unit_tests build

build: build/main.o build/Task.o build/TaskManager.o build/TUIManager.o
	$(CC) $(CCFLAGS) build/main.o build/Task.o build/TaskManager.o build/TUIManager.o -o tmanager

prebuild:
	mkdir -p build

clean:
	rm build/*.o tests/* tmanager 2> /dev/null || true

build/Task.o: src/Task.cpp src/Task.hpp src/utils.hpp | prebuild
	$(CC) $(CCFLAGS) -c src/Task.cpp -o build/Task.o

build/TaskManager.o: src/TaskManager.cpp src/TaskManager.hpp src/Task.hpp src/utils.hpp | prebuild
	$(CC) $(CCFLAGS) -c src/TaskManager.cpp -o build/TaskManager.o

build/TUIManager.o: src/TUIManager.cpp src/TUIManager.hpp src/TaskManager.hpp src/Task.hpp | prebuild
	$(CC) $(CCFLAGS) -c src/TUIManager.cpp -o build/TUIManager.o

build/main.o: src/main.cpp src/TUIManager.hpp | prebuild
	$(CC) $(CCFLAGS) -c src/main.cpp -o build/main.o

test_task: tests/test_task.cpp src/utils.hpp build/Task.o
	$(CC) $(CCFLAGS) tests/test_task.cpp build/Task.o -o tests/test_task $(TESTFLAGS)
	./tests/test_task
	rm ./tests/test_task

test_task_manager: tests/test_task_manager.cpp build/Task.o build/TaskManager.o
	$(CC) $(CCFLAGS) tests/test_task_manager.cpp build/Task.o build/TaskManager.o -o tests/test_task_manager $(TESTFLAGS)
	./tests/test_task_manager
	rm ./tests/test_task_manager

unit_tests: test_task test_task_manager

