# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.29.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.29.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/pawkorchargin/Documents/life/code/paw-regex

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/pawkorchargin/Documents/life/code/paw-regex

# Utility rule file for NightlyTest.

# Include any custom commands dependencies for this target.
include tests/CMakeFiles/NightlyTest.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/NightlyTest.dir/progress.make

tests/CMakeFiles/NightlyTest:
	cd /Users/pawkorchargin/Documents/life/code/paw-regex/tests && /usr/local/Cellar/cmake/3.29.2/bin/ctest -D NightlyTest

NightlyTest: tests/CMakeFiles/NightlyTest
NightlyTest: tests/CMakeFiles/NightlyTest.dir/build.make
.PHONY : NightlyTest

# Rule to build all files generated by this target.
tests/CMakeFiles/NightlyTest.dir/build: NightlyTest
.PHONY : tests/CMakeFiles/NightlyTest.dir/build

tests/CMakeFiles/NightlyTest.dir/clean:
	cd /Users/pawkorchargin/Documents/life/code/paw-regex/tests && $(CMAKE_COMMAND) -P CMakeFiles/NightlyTest.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/NightlyTest.dir/clean

tests/CMakeFiles/NightlyTest.dir/depend:
	cd /Users/pawkorchargin/Documents/life/code/paw-regex && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/pawkorchargin/Documents/life/code/paw-regex /Users/pawkorchargin/Documents/life/code/paw-regex/tests /Users/pawkorchargin/Documents/life/code/paw-regex /Users/pawkorchargin/Documents/life/code/paw-regex/tests /Users/pawkorchargin/Documents/life/code/paw-regex/tests/CMakeFiles/NightlyTest.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : tests/CMakeFiles/NightlyTest.dir/depend

