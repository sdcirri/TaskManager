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
In order to build it you'll need `gettext` and [nlohmann's json](https://github.com/nlohmann/json),
for unit tests I used `libcatch2`.
On debian simply run:
```sh
$ sudo apt install gettext nlohmann-json3-dev libcatch2-dev
```

## Building and running
Simply run `make`, it'll run unit tests and the build a debug
version of the program under `build/tmanager`.
To build the release version run `make release`.
If you want to install the release version, run `sudo make install`,
which will build the release version and install under `/usr/local/bin`.

## Future developments
- [ ] Windows support (I currently use POSIX to get the user's home)
- [X] Localization
- [ ] Sort priorities by expiration
- [ ] Task priorities
  - [ ] Sort by priority
- [ ] GUI (probably Qt6)

