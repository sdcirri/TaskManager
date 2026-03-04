CXX = clang++
CXXFLAGS = -I./src -std=c++20
DBGFLAGS = -g -DLOCALEDIR="\"./locale\"" -o build/tmanager_dbg
RELFLAGS = -DLOCALEDIR="\"/usr/local/share/locale\"" -o build/tmanager
TESTFLAGS = -lCatch2Main -lCatch2

LANGS = en_US it
INSTALL_LANGS = $(LANGS:%=/usr/local/share/locale/%)

.PHONY: clean build debug release install unit_tests test_task test_task_manager i18n

debug: EXTRA = $(DBGFLAGS)
debug: build unit_tests

release: EXTRA = $(RELFLAGS)
release: build

$(INSTALL_LANGS): /usr/local/share/locale/%: locale/%
	mkdir -p $@
	cp -rf $</. $@

install: release $(INSTALL_LANGS)
	cp -f ./build/tmanager /usr/local/bin/tmanager

build: build/main.o build/Task.o build/TaskManager.o build/TUIManager.o i18n
	$(CXX) $(CXXFLAGS) $(EXTRA) build/main.o build/Task.o build/TaskManager.o build/TUIManager.o

prebuild:
	mkdir -p build

clean:
	rm -f build/* tests/test_task test/test_task_manager 2> /dev/null || true

build/Task.o: src/Task.cpp src/Task.hpp src/utils.hpp | prebuild
	$(CXX) $(CXXFLAGS) -c src/Task.cpp -o build/Task.o

build/TaskManager.o: src/TaskManager.cpp src/TaskManager.hpp src/Task.hpp src/utils.hpp | prebuild
	$(CXX) $(CXXFLAGS) -c src/TaskManager.cpp -o build/TaskManager.o

build/TUIManager.o: src/TUIManager.cpp src/TUIManager.hpp src/TaskManager.hpp src/Task.hpp | prebuild
	$(CXX) $(CXXFLAGS) -c src/TUIManager.cpp -o build/TUIManager.o

build/main.o: src/main.cpp src/TUIManager.hpp | prebuild
	$(CXX) $(CXXFLAGS) $(EXTRA) -c src/main.cpp -o build/main.o

test_task: tests/test_task.cpp src/utils.hpp build/Task.o
	$(CXX) $(CXXFLAGS) tests/test_task.cpp build/Task.o -o tests/test_task $(TESTFLAGS)
	./tests/test_task
	rm ./tests/test_task

test_task_manager: tests/test_task_manager.cpp build/Task.o build/TaskManager.o
	$(CXX) $(CXXFLAGS) tests/test_task_manager.cpp build/Task.o build/TaskManager.o -o tests/test_task_manager $(TESTFLAGS)
	./tests/test_task_manager
	rm ./tests/test_task_manager

unit_tests: test_task test_task_manager

i18n: $(LANGS:%=locale/%/LC_MESSAGES/taskmanager.mo)

locale/taskmanager.pot: src/*
	xgettext -k_ -C -o $@ $^

locale/%.po: locale/taskmanager.pot
	[ -f $@ ] && msgmerge -U $@ $< || msginit --locale=$* -i $< -o $@

locale/%/LC_MESSAGES/taskmanager.mo: locale/%.po
	mkdir -p $(dir $@)
	msgfmt $< -o $@

