# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.11

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vv/Code/Gold

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vv/Code/Gold/build

# Include any dependencies generated for this target.
include CMakeFiles/Gold.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Gold.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Gold.dir/flags.make

CMakeFiles/Gold.dir/main.cc.o: CMakeFiles/Gold.dir/flags.make
CMakeFiles/Gold.dir/main.cc.o: ../main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vv/Code/Gold/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Gold.dir/main.cc.o"
	/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Gold.dir/main.cc.o -c /home/vv/Code/Gold/main.cc

CMakeFiles/Gold.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Gold.dir/main.cc.i"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CXX_CREATE_PREPROCESSED_SOURCE

CMakeFiles/Gold.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Gold.dir/main.cc.s"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CXX_CREATE_ASSEMBLY_SOURCE

# Object files for target Gold
Gold_OBJECTS = \
"CMakeFiles/Gold.dir/main.cc.o"

# External object files for target Gold
Gold_EXTERNAL_OBJECTS =

Gold: CMakeFiles/Gold.dir/main.cc.o
Gold: CMakeFiles/Gold.dir/build.make
Gold: CMakeFiles/Gold.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vv/Code/Gold/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Gold"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Gold.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Gold.dir/build: Gold

.PHONY : CMakeFiles/Gold.dir/build

CMakeFiles/Gold.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Gold.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Gold.dir/clean

CMakeFiles/Gold.dir/depend:
	cd /home/vv/Code/Gold/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vv/Code/Gold /home/vv/Code/Gold /home/vv/Code/Gold/build /home/vv/Code/Gold/build /home/vv/Code/Gold/build/CMakeFiles/Gold.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Gold.dir/depend
