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
CMAKE_COMMAND = /snap/clion/98/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/98/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ollie/CLionProjects/Compiler_2.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ollie/CLionProjects/Compiler_2.0/cmake-build-debug

# Include any dependencies generated for this target.
include src/interpreter/CMakeFiles/interpreter.dir/depend.make

# Include the progress variables for this target.
include src/interpreter/CMakeFiles/interpreter.dir/progress.make

# Include the compile flags for this target's objects.
include src/interpreter/CMakeFiles/interpreter.dir/flags.make

src/interpreter/CMakeFiles/interpreter.dir/arithmetic.c.o: src/interpreter/CMakeFiles/interpreter.dir/flags.make
src/interpreter/CMakeFiles/interpreter.dir/arithmetic.c.o: ../src/interpreter/arithmetic.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ollie/CLionProjects/Compiler_2.0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/interpreter/CMakeFiles/interpreter.dir/arithmetic.c.o"
	cd /home/ollie/CLionProjects/Compiler_2.0/cmake-build-debug/src/interpreter && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/interpreter.dir/arithmetic.c.o   -c /home/ollie/CLionProjects/Compiler_2.0/src/interpreter/arithmetic.c

src/interpreter/CMakeFiles/interpreter.dir/arithmetic.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/interpreter.dir/arithmetic.c.i"
	cd /home/ollie/CLionProjects/Compiler_2.0/cmake-build-debug/src/interpreter && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ollie/CLionProjects/Compiler_2.0/src/interpreter/arithmetic.c > CMakeFiles/interpreter.dir/arithmetic.c.i

src/interpreter/CMakeFiles/interpreter.dir/arithmetic.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/interpreter.dir/arithmetic.c.s"
	cd /home/ollie/CLionProjects/Compiler_2.0/cmake-build-debug/src/interpreter && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ollie/CLionProjects/Compiler_2.0/src/interpreter/arithmetic.c -o CMakeFiles/interpreter.dir/arithmetic.c.s

src/interpreter/CMakeFiles/interpreter.dir/interpret.c.o: src/interpreter/CMakeFiles/interpreter.dir/flags.make
src/interpreter/CMakeFiles/interpreter.dir/interpret.c.o: ../src/interpreter/interpret.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ollie/CLionProjects/Compiler_2.0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/interpreter/CMakeFiles/interpreter.dir/interpret.c.o"
	cd /home/ollie/CLionProjects/Compiler_2.0/cmake-build-debug/src/interpreter && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/interpreter.dir/interpret.c.o   -c /home/ollie/CLionProjects/Compiler_2.0/src/interpreter/interpret.c

src/interpreter/CMakeFiles/interpreter.dir/interpret.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/interpreter.dir/interpret.c.i"
	cd /home/ollie/CLionProjects/Compiler_2.0/cmake-build-debug/src/interpreter && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ollie/CLionProjects/Compiler_2.0/src/interpreter/interpret.c > CMakeFiles/interpreter.dir/interpret.c.i

src/interpreter/CMakeFiles/interpreter.dir/interpret.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/interpreter.dir/interpret.c.s"
	cd /home/ollie/CLionProjects/Compiler_2.0/cmake-build-debug/src/interpreter && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ollie/CLionProjects/Compiler_2.0/src/interpreter/interpret.c -o CMakeFiles/interpreter.dir/interpret.c.s

src/interpreter/CMakeFiles/interpreter.dir/debug.c.o: src/interpreter/CMakeFiles/interpreter.dir/flags.make
src/interpreter/CMakeFiles/interpreter.dir/debug.c.o: ../src/interpreter/debug.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ollie/CLionProjects/Compiler_2.0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/interpreter/CMakeFiles/interpreter.dir/debug.c.o"
	cd /home/ollie/CLionProjects/Compiler_2.0/cmake-build-debug/src/interpreter && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/interpreter.dir/debug.c.o   -c /home/ollie/CLionProjects/Compiler_2.0/src/interpreter/debug.c

src/interpreter/CMakeFiles/interpreter.dir/debug.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/interpreter.dir/debug.c.i"
	cd /home/ollie/CLionProjects/Compiler_2.0/cmake-build-debug/src/interpreter && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ollie/CLionProjects/Compiler_2.0/src/interpreter/debug.c > CMakeFiles/interpreter.dir/debug.c.i

src/interpreter/CMakeFiles/interpreter.dir/debug.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/interpreter.dir/debug.c.s"
	cd /home/ollie/CLionProjects/Compiler_2.0/cmake-build-debug/src/interpreter && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ollie/CLionProjects/Compiler_2.0/src/interpreter/debug.c -o CMakeFiles/interpreter.dir/debug.c.s

src/interpreter/CMakeFiles/interpreter.dir/value.c.o: src/interpreter/CMakeFiles/interpreter.dir/flags.make
src/interpreter/CMakeFiles/interpreter.dir/value.c.o: ../src/interpreter/value.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ollie/CLionProjects/Compiler_2.0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object src/interpreter/CMakeFiles/interpreter.dir/value.c.o"
	cd /home/ollie/CLionProjects/Compiler_2.0/cmake-build-debug/src/interpreter && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/interpreter.dir/value.c.o   -c /home/ollie/CLionProjects/Compiler_2.0/src/interpreter/value.c

src/interpreter/CMakeFiles/interpreter.dir/value.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/interpreter.dir/value.c.i"
	cd /home/ollie/CLionProjects/Compiler_2.0/cmake-build-debug/src/interpreter && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ollie/CLionProjects/Compiler_2.0/src/interpreter/value.c > CMakeFiles/interpreter.dir/value.c.i

src/interpreter/CMakeFiles/interpreter.dir/value.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/interpreter.dir/value.c.s"
	cd /home/ollie/CLionProjects/Compiler_2.0/cmake-build-debug/src/interpreter && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ollie/CLionProjects/Compiler_2.0/src/interpreter/value.c -o CMakeFiles/interpreter.dir/value.c.s

# Object files for target interpreter
interpreter_OBJECTS = \
"CMakeFiles/interpreter.dir/arithmetic.c.o" \
"CMakeFiles/interpreter.dir/interpret.c.o" \
"CMakeFiles/interpreter.dir/debug.c.o" \
"CMakeFiles/interpreter.dir/value.c.o"

# External object files for target interpreter
interpreter_EXTERNAL_OBJECTS =

src/interpreter/libinterpreter.a: src/interpreter/CMakeFiles/interpreter.dir/arithmetic.c.o
src/interpreter/libinterpreter.a: src/interpreter/CMakeFiles/interpreter.dir/interpret.c.o
src/interpreter/libinterpreter.a: src/interpreter/CMakeFiles/interpreter.dir/debug.c.o
src/interpreter/libinterpreter.a: src/interpreter/CMakeFiles/interpreter.dir/value.c.o
src/interpreter/libinterpreter.a: src/interpreter/CMakeFiles/interpreter.dir/build.make
src/interpreter/libinterpreter.a: src/interpreter/CMakeFiles/interpreter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ollie/CLionProjects/Compiler_2.0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C static library libinterpreter.a"
	cd /home/ollie/CLionProjects/Compiler_2.0/cmake-build-debug/src/interpreter && $(CMAKE_COMMAND) -P CMakeFiles/interpreter.dir/cmake_clean_target.cmake
	cd /home/ollie/CLionProjects/Compiler_2.0/cmake-build-debug/src/interpreter && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/interpreter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/interpreter/CMakeFiles/interpreter.dir/build: src/interpreter/libinterpreter.a

.PHONY : src/interpreter/CMakeFiles/interpreter.dir/build

src/interpreter/CMakeFiles/interpreter.dir/clean:
	cd /home/ollie/CLionProjects/Compiler_2.0/cmake-build-debug/src/interpreter && $(CMAKE_COMMAND) -P CMakeFiles/interpreter.dir/cmake_clean.cmake
.PHONY : src/interpreter/CMakeFiles/interpreter.dir/clean

src/interpreter/CMakeFiles/interpreter.dir/depend:
	cd /home/ollie/CLionProjects/Compiler_2.0/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ollie/CLionProjects/Compiler_2.0 /home/ollie/CLionProjects/Compiler_2.0/src/interpreter /home/ollie/CLionProjects/Compiler_2.0/cmake-build-debug /home/ollie/CLionProjects/Compiler_2.0/cmake-build-debug/src/interpreter /home/ollie/CLionProjects/Compiler_2.0/cmake-build-debug/src/interpreter/CMakeFiles/interpreter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/interpreter/CMakeFiles/interpreter.dir/depend

