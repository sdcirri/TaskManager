![C++](https://img.shields.io/badge/-c++-blue?logo=c%2B%2B&style=for-the-badge)
![Makefile](https://img.shields.io/badge/-makefile-lightgray?logo=make&style=for-the-badge)
![JSON](https://img.shields.io/badge/-json-orange?logo=json&style=for-the-badge)

# Task Manager
A small project I decided to start in order to get familiar
with all the _quirkiness_ of modern C++ after many years
away from the language.

## Features
This is a simple TUI task manager, you can create tasks with a
title, a description and a due time. You can then mark the tasks
as done, edit them and delete them when you are no longer
interested in them. The tasks are stored in JSON in your user
home (eg. `/home/<username>` in UNIX-like OSes or
`/Users/<username>` in MacOS) under `.local/share/task_manager`.

## Technical details
- I am using C++20 as a standard (planning to switch to C++23)
- I decided to use plain Makefile for building as this project is
(currently) very small
- Modern C++ semantics (`std::optional`, `std::shared_ptr`,
`std::reference_wrapper` and such)

## Dependencies
In order to build it you'll need [nlohmann's json](https://github.com/nlohmann/json),
for unit tests I used `libcatch2`.
On debian simply run:
```sh
$ sudo apt install nlohmann-json3-dev libcatch2-dev
```

## Building and running
Simply run `make`, it'll run unit tests and then build the final
executable under `build/tmanager`, if you want to skip tests run
`make build`, if you only want to run tests run `make unit_tests`.

## Future developments
- [ ] Windows support (I currently use POSIX to get the user's home)
- [ ] Sort priorities by expiration
- [ ] Task priorities
  - [ ] Sort by priority
- [ ] GUI (probably Qt6)

