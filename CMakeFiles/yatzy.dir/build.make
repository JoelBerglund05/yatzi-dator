# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/joel/Documents/GitHub/yatzi-dator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/joel/Documents/GitHub/yatzi-dator

# Include any dependencies generated for this target.
include CMakeFiles/yatzy.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/yatzy.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/yatzy.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/yatzy.dir/flags.make

CMakeFiles/yatzy.dir/main.cpp.o: CMakeFiles/yatzy.dir/flags.make
CMakeFiles/yatzy.dir/main.cpp.o: main.cpp
CMakeFiles/yatzy.dir/main.cpp.o: CMakeFiles/yatzy.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joel/Documents/GitHub/yatzi-dator/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/yatzy.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/yatzy.dir/main.cpp.o -MF CMakeFiles/yatzy.dir/main.cpp.o.d -o CMakeFiles/yatzy.dir/main.cpp.o -c /home/joel/Documents/GitHub/yatzi-dator/main.cpp

CMakeFiles/yatzy.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/yatzy.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joel/Documents/GitHub/yatzi-dator/main.cpp > CMakeFiles/yatzy.dir/main.cpp.i

CMakeFiles/yatzy.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/yatzy.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joel/Documents/GitHub/yatzi-dator/main.cpp -o CMakeFiles/yatzy.dir/main.cpp.s

# Object files for target yatzy
yatzy_OBJECTS = \
"CMakeFiles/yatzy.dir/main.cpp.o"

# External object files for target yatzy
yatzy_EXTERNAL_OBJECTS =

yatzy: CMakeFiles/yatzy.dir/main.cpp.o
yatzy: CMakeFiles/yatzy.dir/build.make
yatzy: CMakeFiles/yatzy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/joel/Documents/GitHub/yatzi-dator/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable yatzy"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/yatzy.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/yatzy.dir/build: yatzy
.PHONY : CMakeFiles/yatzy.dir/build

CMakeFiles/yatzy.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/yatzy.dir/cmake_clean.cmake
.PHONY : CMakeFiles/yatzy.dir/clean

CMakeFiles/yatzy.dir/depend:
	cd /home/joel/Documents/GitHub/yatzi-dator && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joel/Documents/GitHub/yatzi-dator /home/joel/Documents/GitHub/yatzi-dator /home/joel/Documents/GitHub/yatzi-dator /home/joel/Documents/GitHub/yatzi-dator /home/joel/Documents/GitHub/yatzi-dator/CMakeFiles/yatzy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/yatzy.dir/depend

