# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.5/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/build"

# Utility rule file for atm_system_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/atm_system_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/atm_system_autogen.dir/progress.make

CMakeFiles/atm_system_autogen: atm_system_autogen/timestamp

atm_system_autogen/timestamp: /opt/homebrew/share/qt/libexec/moc
atm_system_autogen/timestamp: /opt/homebrew/share/qt/libexec/uic
atm_system_autogen/timestamp: CMakeFiles/atm_system_autogen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir="/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target atm_system"
	/opt/homebrew/Cellar/cmake/3.30.5/bin/cmake -E cmake_autogen "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/build/CMakeFiles/atm_system_autogen.dir/AutogenInfo.json" ""
	/opt/homebrew/Cellar/cmake/3.30.5/bin/cmake -E touch "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/build/atm_system_autogen/timestamp"

atm_system_autogen: CMakeFiles/atm_system_autogen
atm_system_autogen: atm_system_autogen/timestamp
atm_system_autogen: CMakeFiles/atm_system_autogen.dir/build.make
.PHONY : atm_system_autogen

# Rule to build all files generated by this target.
CMakeFiles/atm_system_autogen.dir/build: atm_system_autogen
.PHONY : CMakeFiles/atm_system_autogen.dir/build

CMakeFiles/atm_system_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/atm_system_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/atm_system_autogen.dir/clean

CMakeFiles/atm_system_autogen.dir/depend:
	cd "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project" "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project" "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/build" "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/build" "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/build/CMakeFiles/atm_system_autogen.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/atm_system_autogen.dir/depend

