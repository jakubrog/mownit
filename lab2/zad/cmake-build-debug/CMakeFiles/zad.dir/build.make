# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = "/Users/jakubrog/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/183.5429.37/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/jakubrog/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/183.5429.37/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jakubrog/mownit/lab2/zad

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jakubrog/mownit/lab2/zad/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/zad.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/zad.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/zad.dir/flags.make

CMakeFiles/zad.dir/main.c.o: CMakeFiles/zad.dir/flags.make
CMakeFiles/zad.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jakubrog/mownit/lab2/zad/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/zad.dir/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/zad.dir/main.c.o   -c /Users/jakubrog/mownit/lab2/zad/main.c

CMakeFiles/zad.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zad.dir/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/jakubrog/mownit/lab2/zad/main.c > CMakeFiles/zad.dir/main.c.i

CMakeFiles/zad.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zad.dir/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/jakubrog/mownit/lab2/zad/main.c -o CMakeFiles/zad.dir/main.c.s

# Object files for target zad
zad_OBJECTS = \
"CMakeFiles/zad.dir/main.c.o"

# External object files for target zad
zad_EXTERNAL_OBJECTS =

zad: CMakeFiles/zad.dir/main.c.o
zad: CMakeFiles/zad.dir/build.make
zad: /usr/local/lib/libgsl.dylib
zad: /usr/local/lib/libgslcblas.dylib
zad: CMakeFiles/zad.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jakubrog/mownit/lab2/zad/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable zad"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/zad.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/zad.dir/build: zad

.PHONY : CMakeFiles/zad.dir/build

CMakeFiles/zad.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/zad.dir/cmake_clean.cmake
.PHONY : CMakeFiles/zad.dir/clean

CMakeFiles/zad.dir/depend:
	cd /Users/jakubrog/mownit/lab2/zad/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jakubrog/mownit/lab2/zad /Users/jakubrog/mownit/lab2/zad /Users/jakubrog/mownit/lab2/zad/cmake-build-debug /Users/jakubrog/mownit/lab2/zad/cmake-build-debug /Users/jakubrog/mownit/lab2/zad/cmake-build-debug/CMakeFiles/zad.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/zad.dir/depend

