# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\or\CLionProjects\PS\HW1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\or\CLionProjects\PS\HW1\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/HW1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/HW1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HW1.dir/flags.make

CMakeFiles/HW1.dir/kmeans.c.obj: CMakeFiles/HW1.dir/flags.make
CMakeFiles/HW1.dir/kmeans.c.obj: ../kmeans.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\or\CLionProjects\PS\HW1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/HW1.dir/kmeans.c.obj"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\HW1.dir\kmeans.c.obj   -c C:\Users\or\CLionProjects\PS\HW1\kmeans.c

CMakeFiles/HW1.dir/kmeans.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/HW1.dir/kmeans.c.i"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\or\CLionProjects\PS\HW1\kmeans.c > CMakeFiles\HW1.dir\kmeans.c.i

CMakeFiles/HW1.dir/kmeans.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/HW1.dir/kmeans.c.s"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\or\CLionProjects\PS\HW1\kmeans.c -o CMakeFiles\HW1.dir\kmeans.c.s

CMakeFiles/HW1.dir/test.c.obj: CMakeFiles/HW1.dir/flags.make
CMakeFiles/HW1.dir/test.c.obj: ../test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\or\CLionProjects\PS\HW1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/HW1.dir/test.c.obj"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\HW1.dir\test.c.obj   -c C:\Users\or\CLionProjects\PS\HW1\test.c

CMakeFiles/HW1.dir/test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/HW1.dir/test.c.i"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\or\CLionProjects\PS\HW1\test.c > CMakeFiles\HW1.dir\test.c.i

CMakeFiles/HW1.dir/test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/HW1.dir/test.c.s"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\or\CLionProjects\PS\HW1\test.c -o CMakeFiles\HW1.dir\test.c.s

# Object files for target HW1
HW1_OBJECTS = \
"CMakeFiles/HW1.dir/kmeans.c.obj" \
"CMakeFiles/HW1.dir/test.c.obj"

# External object files for target HW1
HW1_EXTERNAL_OBJECTS =

HW1.exe: CMakeFiles/HW1.dir/kmeans.c.obj
HW1.exe: CMakeFiles/HW1.dir/test.c.obj
HW1.exe: CMakeFiles/HW1.dir/build.make
HW1.exe: CMakeFiles/HW1.dir/linklibs.rsp
HW1.exe: CMakeFiles/HW1.dir/objects1.rsp
HW1.exe: CMakeFiles/HW1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\or\CLionProjects\PS\HW1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable HW1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\HW1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HW1.dir/build: HW1.exe

.PHONY : CMakeFiles/HW1.dir/build

CMakeFiles/HW1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\HW1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/HW1.dir/clean

CMakeFiles/HW1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\or\CLionProjects\PS\HW1 C:\Users\or\CLionProjects\PS\HW1 C:\Users\or\CLionProjects\PS\HW1\cmake-build-debug C:\Users\or\CLionProjects\PS\HW1\cmake-build-debug C:\Users\or\CLionProjects\PS\HW1\cmake-build-debug\CMakeFiles\HW1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HW1.dir/depend

