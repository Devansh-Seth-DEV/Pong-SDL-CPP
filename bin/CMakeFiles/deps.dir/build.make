# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/devansh/C_C++/SDL_Learning/Practice

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/devansh/C_C++/SDL_Learning/Practice/bin

# Utility rule file for deps.

# Include any custom commands dependencies for this target.
include CMakeFiles/deps.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/deps.dir/progress.make

CMakeFiles/deps:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/devansh/C_C++/SDL_Learning/Practice/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Creating dependencies"
	/usr/bin/cmake -E copy_directory /home/devansh/C_C++/SDL_Learning/Practice/assets /home/devansh/C_C++/SDL_Learning/Practice/bin/assets

deps: CMakeFiles/deps
deps: CMakeFiles/deps.dir/build.make
.PHONY : deps

# Rule to build all files generated by this target.
CMakeFiles/deps.dir/build: deps
.PHONY : CMakeFiles/deps.dir/build

CMakeFiles/deps.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/deps.dir/cmake_clean.cmake
.PHONY : CMakeFiles/deps.dir/clean

CMakeFiles/deps.dir/depend:
	cd /home/devansh/C_C++/SDL_Learning/Practice/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/devansh/C_C++/SDL_Learning/Practice /home/devansh/C_C++/SDL_Learning/Practice /home/devansh/C_C++/SDL_Learning/Practice/bin /home/devansh/C_C++/SDL_Learning/Practice/bin /home/devansh/C_C++/SDL_Learning/Practice/bin/CMakeFiles/deps.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/deps.dir/depend

