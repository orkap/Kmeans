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
CMAKE_SOURCE_DIR = C:\Users\or\Documents\School\SP\HW1\HW1_C

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\or\Documents\School\SP\HW1\HW1_C\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/HW1_C.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/HW1_C.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HW1_C.dir/flags.make

CMakeFiles/HW1_C.dir/kmeans.c.obj: CMakeFiles/HW1_C.dir/flags.make
CMakeFiles/HW1_C.dir/kmeans.c.obj: ../kmeans.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\or\Documents\School\SP\HW1\HW1_C\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/HW1_C.dir/kmeans.c.obj"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\HW1_C.dir\kmeans.c.obj   -c C:\Users\or\Documents\School\SP\HW1\HW1_C\kmeans.c

CMakeFiles/HW1_C.dir/kmeans.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/HW1_C.dir/kmeans.c.i"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\or\Documents\School\SP\HW1\HW1_C\kmeans.c > CMakeFiles\HW1_C.dir\kmeans.c.i

CMakeFiles/HW1_C.dir/kmeans.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/HW1_C.dir/kmeans.c.s"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\or\Documents\School\SP\HW1\HW1_C\kmeans.c -o CMakeFiles\HW1_C.dir\kmeans.c.s

# Object files for target HW1_C
HW1_C_OBJECTS = \
"CMakeFiles/HW1_C.dir/kmeans.c.obj"

# External object files for target HW1_C
HW1_C_EXTERNAL_OBJECTS =

HW1_C.exe: CMakeFiles/HW1_C.dir/kmeans.c.obj
HW1_C.exe: CMakeFiles/HW1_C.dir/build.make
HW1_C.exe: CMakeFiles/HW1_C.dir/linklibs.rsp
HW1_C.exe: CMakeFiles/HW1_C.dir/objects1.rsp
HW1_C.exe: CMakeFiles/HW1_C.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\or\Documents\School\SP\HW1\HW1_C\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable HW1_C.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\HW1_C.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HW1_C.dir/build: HW1_C.exe

.PHONY : CMakeFiles/HW1_C.dir/build

CMakeFiles/HW1_C.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\HW1_C.dir\cmake_clean.cmake
.PHONY : CMakeFiles/HW1_C.dir/clean

CMakeFiles/HW1_C.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\or\Documents\School\SP\HW1\HW1_C C:\Users\or\Documents\School\SP\HW1\HW1_C C:\Users\or\Documents\School\SP\HW1\HW1_C\cmake-build-debug C:\Users\or\Documents\School\SP\HW1\HW1_C\cmake-build-debug C:\Users\or\Documents\School\SP\HW1\HW1_C\cmake-build-debug\CMakeFiles\HW1_C.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HW1_C.dir/depend

