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

# Include any dependencies generated for this target.
include CMakeFiles/atm_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/atm_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/atm_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/atm_test.dir/flags.make

CMakeFiles/atm_test.dir/test/test_atm.cpp.o: CMakeFiles/atm_test.dir/flags.make
CMakeFiles/atm_test.dir/test/test_atm.cpp.o: /Users/thet/Desktop/Work/Current/Loop\ Dimension/Projects/atm_project/test/test_atm.cpp
CMakeFiles/atm_test.dir/test/test_atm.cpp.o: CMakeFiles/atm_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/atm_test.dir/test/test_atm.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/atm_test.dir/test/test_atm.cpp.o -MF CMakeFiles/atm_test.dir/test/test_atm.cpp.o.d -o CMakeFiles/atm_test.dir/test/test_atm.cpp.o -c "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/test/test_atm.cpp"

CMakeFiles/atm_test.dir/test/test_atm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/atm_test.dir/test/test_atm.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/test/test_atm.cpp" > CMakeFiles/atm_test.dir/test/test_atm.cpp.i

CMakeFiles/atm_test.dir/test/test_atm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/atm_test.dir/test/test_atm.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/test/test_atm.cpp" -o CMakeFiles/atm_test.dir/test/test_atm.cpp.s

CMakeFiles/atm_test.dir/src/UI.cpp.o: CMakeFiles/atm_test.dir/flags.make
CMakeFiles/atm_test.dir/src/UI.cpp.o: /Users/thet/Desktop/Work/Current/Loop\ Dimension/Projects/atm_project/src/UI.cpp
CMakeFiles/atm_test.dir/src/UI.cpp.o: CMakeFiles/atm_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/atm_test.dir/src/UI.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/atm_test.dir/src/UI.cpp.o -MF CMakeFiles/atm_test.dir/src/UI.cpp.o.d -o CMakeFiles/atm_test.dir/src/UI.cpp.o -c "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/src/UI.cpp"

CMakeFiles/atm_test.dir/src/UI.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/atm_test.dir/src/UI.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/src/UI.cpp" > CMakeFiles/atm_test.dir/src/UI.cpp.i

CMakeFiles/atm_test.dir/src/UI.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/atm_test.dir/src/UI.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/src/UI.cpp" -o CMakeFiles/atm_test.dir/src/UI.cpp.s

CMakeFiles/atm_test.dir/src/SystemInitializer.cpp.o: CMakeFiles/atm_test.dir/flags.make
CMakeFiles/atm_test.dir/src/SystemInitializer.cpp.o: /Users/thet/Desktop/Work/Current/Loop\ Dimension/Projects/atm_project/src/SystemInitializer.cpp
CMakeFiles/atm_test.dir/src/SystemInitializer.cpp.o: CMakeFiles/atm_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/atm_test.dir/src/SystemInitializer.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/atm_test.dir/src/SystemInitializer.cpp.o -MF CMakeFiles/atm_test.dir/src/SystemInitializer.cpp.o.d -o CMakeFiles/atm_test.dir/src/SystemInitializer.cpp.o -c "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/src/SystemInitializer.cpp"

CMakeFiles/atm_test.dir/src/SystemInitializer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/atm_test.dir/src/SystemInitializer.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/src/SystemInitializer.cpp" > CMakeFiles/atm_test.dir/src/SystemInitializer.cpp.i

CMakeFiles/atm_test.dir/src/SystemInitializer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/atm_test.dir/src/SystemInitializer.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/src/SystemInitializer.cpp" -o CMakeFiles/atm_test.dir/src/SystemInitializer.cpp.s

CMakeFiles/atm_test.dir/src/ATM.cpp.o: CMakeFiles/atm_test.dir/flags.make
CMakeFiles/atm_test.dir/src/ATM.cpp.o: /Users/thet/Desktop/Work/Current/Loop\ Dimension/Projects/atm_project/src/ATM.cpp
CMakeFiles/atm_test.dir/src/ATM.cpp.o: CMakeFiles/atm_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/atm_test.dir/src/ATM.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/atm_test.dir/src/ATM.cpp.o -MF CMakeFiles/atm_test.dir/src/ATM.cpp.o.d -o CMakeFiles/atm_test.dir/src/ATM.cpp.o -c "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/src/ATM.cpp"

CMakeFiles/atm_test.dir/src/ATM.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/atm_test.dir/src/ATM.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/src/ATM.cpp" > CMakeFiles/atm_test.dir/src/ATM.cpp.i

CMakeFiles/atm_test.dir/src/ATM.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/atm_test.dir/src/ATM.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/src/ATM.cpp" -o CMakeFiles/atm_test.dir/src/ATM.cpp.s

CMakeFiles/atm_test.dir/src/Bank.cpp.o: CMakeFiles/atm_test.dir/flags.make
CMakeFiles/atm_test.dir/src/Bank.cpp.o: /Users/thet/Desktop/Work/Current/Loop\ Dimension/Projects/atm_project/src/Bank.cpp
CMakeFiles/atm_test.dir/src/Bank.cpp.o: CMakeFiles/atm_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/atm_test.dir/src/Bank.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/atm_test.dir/src/Bank.cpp.o -MF CMakeFiles/atm_test.dir/src/Bank.cpp.o.d -o CMakeFiles/atm_test.dir/src/Bank.cpp.o -c "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/src/Bank.cpp"

CMakeFiles/atm_test.dir/src/Bank.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/atm_test.dir/src/Bank.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/src/Bank.cpp" > CMakeFiles/atm_test.dir/src/Bank.cpp.i

CMakeFiles/atm_test.dir/src/Bank.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/atm_test.dir/src/Bank.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/src/Bank.cpp" -o CMakeFiles/atm_test.dir/src/Bank.cpp.s

CMakeFiles/atm_test.dir/src/Account.cpp.o: CMakeFiles/atm_test.dir/flags.make
CMakeFiles/atm_test.dir/src/Account.cpp.o: /Users/thet/Desktop/Work/Current/Loop\ Dimension/Projects/atm_project/src/Account.cpp
CMakeFiles/atm_test.dir/src/Account.cpp.o: CMakeFiles/atm_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/atm_test.dir/src/Account.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/atm_test.dir/src/Account.cpp.o -MF CMakeFiles/atm_test.dir/src/Account.cpp.o.d -o CMakeFiles/atm_test.dir/src/Account.cpp.o -c "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/src/Account.cpp"

CMakeFiles/atm_test.dir/src/Account.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/atm_test.dir/src/Account.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/src/Account.cpp" > CMakeFiles/atm_test.dir/src/Account.cpp.i

CMakeFiles/atm_test.dir/src/Account.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/atm_test.dir/src/Account.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/src/Account.cpp" -o CMakeFiles/atm_test.dir/src/Account.cpp.s

CMakeFiles/atm_test.dir/src/Transaction.cpp.o: CMakeFiles/atm_test.dir/flags.make
CMakeFiles/atm_test.dir/src/Transaction.cpp.o: /Users/thet/Desktop/Work/Current/Loop\ Dimension/Projects/atm_project/src/Transaction.cpp
CMakeFiles/atm_test.dir/src/Transaction.cpp.o: CMakeFiles/atm_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/atm_test.dir/src/Transaction.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/atm_test.dir/src/Transaction.cpp.o -MF CMakeFiles/atm_test.dir/src/Transaction.cpp.o.d -o CMakeFiles/atm_test.dir/src/Transaction.cpp.o -c "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/src/Transaction.cpp"

CMakeFiles/atm_test.dir/src/Transaction.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/atm_test.dir/src/Transaction.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/src/Transaction.cpp" > CMakeFiles/atm_test.dir/src/Transaction.cpp.i

CMakeFiles/atm_test.dir/src/Transaction.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/atm_test.dir/src/Transaction.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/src/Transaction.cpp" -o CMakeFiles/atm_test.dir/src/Transaction.cpp.s

# Object files for target atm_test
atm_test_OBJECTS = \
"CMakeFiles/atm_test.dir/test/test_atm.cpp.o" \
"CMakeFiles/atm_test.dir/src/UI.cpp.o" \
"CMakeFiles/atm_test.dir/src/SystemInitializer.cpp.o" \
"CMakeFiles/atm_test.dir/src/ATM.cpp.o" \
"CMakeFiles/atm_test.dir/src/Bank.cpp.o" \
"CMakeFiles/atm_test.dir/src/Account.cpp.o" \
"CMakeFiles/atm_test.dir/src/Transaction.cpp.o"

# External object files for target atm_test
atm_test_EXTERNAL_OBJECTS =

atm_test: CMakeFiles/atm_test.dir/test/test_atm.cpp.o
atm_test: CMakeFiles/atm_test.dir/src/UI.cpp.o
atm_test: CMakeFiles/atm_test.dir/src/SystemInitializer.cpp.o
atm_test: CMakeFiles/atm_test.dir/src/ATM.cpp.o
atm_test: CMakeFiles/atm_test.dir/src/Bank.cpp.o
atm_test: CMakeFiles/atm_test.dir/src/Account.cpp.o
atm_test: CMakeFiles/atm_test.dir/src/Transaction.cpp.o
atm_test: CMakeFiles/atm_test.dir/build.make
atm_test: CMakeFiles/atm_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable atm_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/atm_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/atm_test.dir/build: atm_test
.PHONY : CMakeFiles/atm_test.dir/build

CMakeFiles/atm_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/atm_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/atm_test.dir/clean

CMakeFiles/atm_test.dir/depend:
	cd "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project" "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project" "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/build" "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/build" "/Users/thet/Desktop/Work/Current/Loop Dimension/Projects/atm_project/build/CMakeFiles/atm_test.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/atm_test.dir/depend

