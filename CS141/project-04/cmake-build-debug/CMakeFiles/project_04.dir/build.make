# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/rak3rman/Documents/CLionProjects/CS141/project_04

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/rak3rman/Documents/CLionProjects/CS141/project_04/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/project_04.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/project_04.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/project_04.dir/flags.make

CMakeFiles/project_04.dir/main.cpp.o: CMakeFiles/project_04.dir/flags.make
CMakeFiles/project_04.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/rak3rman/Documents/CLionProjects/CS141/project_04/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/project_04.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project_04.dir/main.cpp.o -c /Users/rak3rman/Documents/CLionProjects/CS141/project_04/main.cpp

CMakeFiles/project_04.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project_04.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/rak3rman/Documents/CLionProjects/CS141/project_04/main.cpp > CMakeFiles/project_04.dir/main.cpp.i

CMakeFiles/project_04.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project_04.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/rak3rman/Documents/CLionProjects/CS141/project_04/main.cpp -o CMakeFiles/project_04.dir/main.cpp.s

CMakeFiles/project_04.dir/token.cpp.o: CMakeFiles/project_04.dir/flags.make
CMakeFiles/project_04.dir/token.cpp.o: ../token.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/rak3rman/Documents/CLionProjects/CS141/project_04/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/project_04.dir/token.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project_04.dir/token.cpp.o -c /Users/rak3rman/Documents/CLionProjects/CS141/project_04/token.cpp

CMakeFiles/project_04.dir/token.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project_04.dir/token.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/rak3rman/Documents/CLionProjects/CS141/project_04/token.cpp > CMakeFiles/project_04.dir/token.cpp.i

CMakeFiles/project_04.dir/token.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project_04.dir/token.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/rak3rman/Documents/CLionProjects/CS141/project_04/token.cpp -o CMakeFiles/project_04.dir/token.cpp.s

CMakeFiles/project_04.dir/parser.cpp.o: CMakeFiles/project_04.dir/flags.make
CMakeFiles/project_04.dir/parser.cpp.o: ../parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/rak3rman/Documents/CLionProjects/CS141/project_04/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/project_04.dir/parser.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project_04.dir/parser.cpp.o -c /Users/rak3rman/Documents/CLionProjects/CS141/project_04/parser.cpp

CMakeFiles/project_04.dir/parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project_04.dir/parser.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/rak3rman/Documents/CLionProjects/CS141/project_04/parser.cpp > CMakeFiles/project_04.dir/parser.cpp.i

CMakeFiles/project_04.dir/parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project_04.dir/parser.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/rak3rman/Documents/CLionProjects/CS141/project_04/parser.cpp -o CMakeFiles/project_04.dir/parser.cpp.s

# Object files for target project_04
project_04_OBJECTS = \
"CMakeFiles/project_04.dir/main.cpp.o" \
"CMakeFiles/project_04.dir/token.cpp.o" \
"CMakeFiles/project_04.dir/parser.cpp.o"

# External object files for target project_04
project_04_EXTERNAL_OBJECTS =

project_04: CMakeFiles/project_04.dir/main.cpp.o
project_04: CMakeFiles/project_04.dir/token.cpp.o
project_04: CMakeFiles/project_04.dir/parser.cpp.o
project_04: CMakeFiles/project_04.dir/build.make
project_04: CMakeFiles/project_04.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/rak3rman/Documents/CLionProjects/CS141/project_04/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable project_04"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/project_04.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/project_04.dir/build: project_04

.PHONY : CMakeFiles/project_04.dir/build

CMakeFiles/project_04.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/project_04.dir/cmake_clean.cmake
.PHONY : CMakeFiles/project_04.dir/clean

CMakeFiles/project_04.dir/depend:
	cd /Users/rak3rman/Documents/CLionProjects/CS141/project_04/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/rak3rman/Documents/CLionProjects/CS141/project_04 /Users/rak3rman/Documents/CLionProjects/CS141/project_04 /Users/rak3rman/Documents/CLionProjects/CS141/project_04/cmake-build-debug /Users/rak3rman/Documents/CLionProjects/CS141/project_04/cmake-build-debug /Users/rak3rman/Documents/CLionProjects/CS141/project_04/cmake-build-debug/CMakeFiles/project_04.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/project_04.dir/depend

