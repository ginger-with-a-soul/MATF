# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/dimitrije/Downloads/clion-2019.2.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/dimitrije/Downloads/clion-2019.2.3/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/dimitrije/Desktop/Operativni sistemi/cas4"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/dimitrije/Desktop/Operativni sistemi/cas4/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/cas4.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cas4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cas4.dir/flags.make

CMakeFiles/cas4.dir/filterFilesByExt.c.o: CMakeFiles/cas4.dir/flags.make
CMakeFiles/cas4.dir/filterFilesByExt.c.o: ../filterFilesByExt.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/dimitrije/Desktop/Operativni sistemi/cas4/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/cas4.dir/filterFilesByExt.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cas4.dir/filterFilesByExt.c.o   -c "/home/dimitrije/Desktop/Operativni sistemi/cas4/filterFilesByExt.c"

CMakeFiles/cas4.dir/filterFilesByExt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cas4.dir/filterFilesByExt.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/dimitrije/Desktop/Operativni sistemi/cas4/filterFilesByExt.c" > CMakeFiles/cas4.dir/filterFilesByExt.c.i

CMakeFiles/cas4.dir/filterFilesByExt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cas4.dir/filterFilesByExt.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/dimitrije/Desktop/Operativni sistemi/cas4/filterFilesByExt.c" -o CMakeFiles/cas4.dir/filterFilesByExt.c.s

# Object files for target cas4
cas4_OBJECTS = \
"CMakeFiles/cas4.dir/filterFilesByExt.c.o"

# External object files for target cas4
cas4_EXTERNAL_OBJECTS =

cas4: CMakeFiles/cas4.dir/filterFilesByExt.c.o
cas4: CMakeFiles/cas4.dir/build.make
cas4: CMakeFiles/cas4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/dimitrije/Desktop/Operativni sistemi/cas4/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable cas4"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cas4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cas4.dir/build: cas4

.PHONY : CMakeFiles/cas4.dir/build

CMakeFiles/cas4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cas4.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cas4.dir/clean

CMakeFiles/cas4.dir/depend:
	cd "/home/dimitrije/Desktop/Operativni sistemi/cas4/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/dimitrije/Desktop/Operativni sistemi/cas4" "/home/dimitrije/Desktop/Operativni sistemi/cas4" "/home/dimitrije/Desktop/Operativni sistemi/cas4/cmake-build-debug" "/home/dimitrije/Desktop/Operativni sistemi/cas4/cmake-build-debug" "/home/dimitrije/Desktop/Operativni sistemi/cas4/cmake-build-debug/CMakeFiles/cas4.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/cas4.dir/depend

