# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /nix/store/rxb9zl1mdx9f2n3z0nyv9zhngj3f2pw0-cmake-3.24.3/bin/cmake

# The command to remove a file.
RM = /nix/store/rxb9zl1mdx9f2n3z0nyv9zhngj3f2pw0-cmake-3.24.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/runner/Sem3Lab2/2Simple

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/runner/Sem3Lab2/2Simple/build

# Include any dependencies generated for this target.
include CMakeFiles/simpleClass.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/simpleClass.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/simpleClass.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/simpleClass.dir/flags.make

CMakeFiles/simpleClass.dir/mainSimpleClass.cpp.o: CMakeFiles/simpleClass.dir/flags.make
CMakeFiles/simpleClass.dir/mainSimpleClass.cpp.o: /home/runner/Sem3Lab2/2Simple/mainSimpleClass.cpp
CMakeFiles/simpleClass.dir/mainSimpleClass.cpp.o: CMakeFiles/simpleClass.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/runner/Sem3Lab2/2Simple/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/simpleClass.dir/mainSimpleClass.cpp.o"
	/nix/store/dq0xwmsk1g0i2ayg6pb7y87na2knzylh-gcc-wrapper-11.3.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/simpleClass.dir/mainSimpleClass.cpp.o -MF CMakeFiles/simpleClass.dir/mainSimpleClass.cpp.o.d -o CMakeFiles/simpleClass.dir/mainSimpleClass.cpp.o -c /home/runner/Sem3Lab2/2Simple/mainSimpleClass.cpp

CMakeFiles/simpleClass.dir/mainSimpleClass.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simpleClass.dir/mainSimpleClass.cpp.i"
	/nix/store/dq0xwmsk1g0i2ayg6pb7y87na2knzylh-gcc-wrapper-11.3.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/runner/Sem3Lab2/2Simple/mainSimpleClass.cpp > CMakeFiles/simpleClass.dir/mainSimpleClass.cpp.i

CMakeFiles/simpleClass.dir/mainSimpleClass.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simpleClass.dir/mainSimpleClass.cpp.s"
	/nix/store/dq0xwmsk1g0i2ayg6pb7y87na2knzylh-gcc-wrapper-11.3.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/runner/Sem3Lab2/2Simple/mainSimpleClass.cpp -o CMakeFiles/simpleClass.dir/mainSimpleClass.cpp.s

# Object files for target simpleClass
simpleClass_OBJECTS = \
"CMakeFiles/simpleClass.dir/mainSimpleClass.cpp.o"

# External object files for target simpleClass
simpleClass_EXTERNAL_OBJECTS =

simpleClass: CMakeFiles/simpleClass.dir/mainSimpleClass.cpp.o
simpleClass: CMakeFiles/simpleClass.dir/build.make
simpleClass: wagon/libwagon.a
simpleClass: CMakeFiles/simpleClass.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/runner/Sem3Lab2/2Simple/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable simpleClass"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/simpleClass.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/simpleClass.dir/build: simpleClass
.PHONY : CMakeFiles/simpleClass.dir/build

CMakeFiles/simpleClass.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/simpleClass.dir/cmake_clean.cmake
.PHONY : CMakeFiles/simpleClass.dir/clean

CMakeFiles/simpleClass.dir/depend:
	cd /home/runner/Sem3Lab2/2Simple/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/runner/Sem3Lab2/2Simple /home/runner/Sem3Lab2/2Simple /home/runner/Sem3Lab2/2Simple/build /home/runner/Sem3Lab2/2Simple/build /home/runner/Sem3Lab2/2Simple/build/CMakeFiles/simpleClass.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/simpleClass.dir/depend

