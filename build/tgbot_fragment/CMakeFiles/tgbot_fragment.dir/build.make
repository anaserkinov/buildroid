# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/anaskhan/proj/botmaestro

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anaskhan/proj/botmaestro/build

# Include any dependencies generated for this target.
include tgbot_fragment/CMakeFiles/tgbot_fragment.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tgbot_fragment/CMakeFiles/tgbot_fragment.dir/compiler_depend.make

# Include the progress variables for this target.
include tgbot_fragment/CMakeFiles/tgbot_fragment.dir/progress.make

# Include the compile flags for this target's objects.
include tgbot_fragment/CMakeFiles/tgbot_fragment.dir/flags.make

tgbot_fragment/CMakeFiles/tgbot_fragment.dir/src/Fragment.cpp.o: tgbot_fragment/CMakeFiles/tgbot_fragment.dir/flags.make
tgbot_fragment/CMakeFiles/tgbot_fragment.dir/src/Fragment.cpp.o: ../tgbot_fragment/src/Fragment.cpp
tgbot_fragment/CMakeFiles/tgbot_fragment.dir/src/Fragment.cpp.o: tgbot_fragment/CMakeFiles/tgbot_fragment.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anaskhan/proj/botmaestro/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tgbot_fragment/CMakeFiles/tgbot_fragment.dir/src/Fragment.cpp.o"
	cd /home/anaskhan/proj/botmaestro/build/tgbot_fragment && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tgbot_fragment/CMakeFiles/tgbot_fragment.dir/src/Fragment.cpp.o -MF CMakeFiles/tgbot_fragment.dir/src/Fragment.cpp.o.d -o CMakeFiles/tgbot_fragment.dir/src/Fragment.cpp.o -c /home/anaskhan/proj/botmaestro/tgbot_fragment/src/Fragment.cpp

tgbot_fragment/CMakeFiles/tgbot_fragment.dir/src/Fragment.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tgbot_fragment.dir/src/Fragment.cpp.i"
	cd /home/anaskhan/proj/botmaestro/build/tgbot_fragment && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anaskhan/proj/botmaestro/tgbot_fragment/src/Fragment.cpp > CMakeFiles/tgbot_fragment.dir/src/Fragment.cpp.i

tgbot_fragment/CMakeFiles/tgbot_fragment.dir/src/Fragment.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tgbot_fragment.dir/src/Fragment.cpp.s"
	cd /home/anaskhan/proj/botmaestro/build/tgbot_fragment && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anaskhan/proj/botmaestro/tgbot_fragment/src/Fragment.cpp -o CMakeFiles/tgbot_fragment.dir/src/Fragment.cpp.s

tgbot_fragment/CMakeFiles/tgbot_fragment.dir/src/FragmentManager.cpp.o: tgbot_fragment/CMakeFiles/tgbot_fragment.dir/flags.make
tgbot_fragment/CMakeFiles/tgbot_fragment.dir/src/FragmentManager.cpp.o: ../tgbot_fragment/src/FragmentManager.cpp
tgbot_fragment/CMakeFiles/tgbot_fragment.dir/src/FragmentManager.cpp.o: tgbot_fragment/CMakeFiles/tgbot_fragment.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anaskhan/proj/botmaestro/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object tgbot_fragment/CMakeFiles/tgbot_fragment.dir/src/FragmentManager.cpp.o"
	cd /home/anaskhan/proj/botmaestro/build/tgbot_fragment && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tgbot_fragment/CMakeFiles/tgbot_fragment.dir/src/FragmentManager.cpp.o -MF CMakeFiles/tgbot_fragment.dir/src/FragmentManager.cpp.o.d -o CMakeFiles/tgbot_fragment.dir/src/FragmentManager.cpp.o -c /home/anaskhan/proj/botmaestro/tgbot_fragment/src/FragmentManager.cpp

tgbot_fragment/CMakeFiles/tgbot_fragment.dir/src/FragmentManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tgbot_fragment.dir/src/FragmentManager.cpp.i"
	cd /home/anaskhan/proj/botmaestro/build/tgbot_fragment && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anaskhan/proj/botmaestro/tgbot_fragment/src/FragmentManager.cpp > CMakeFiles/tgbot_fragment.dir/src/FragmentManager.cpp.i

tgbot_fragment/CMakeFiles/tgbot_fragment.dir/src/FragmentManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tgbot_fragment.dir/src/FragmentManager.cpp.s"
	cd /home/anaskhan/proj/botmaestro/build/tgbot_fragment && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anaskhan/proj/botmaestro/tgbot_fragment/src/FragmentManager.cpp -o CMakeFiles/tgbot_fragment.dir/src/FragmentManager.cpp.s

# Object files for target tgbot_fragment
tgbot_fragment_OBJECTS = \
"CMakeFiles/tgbot_fragment.dir/src/Fragment.cpp.o" \
"CMakeFiles/tgbot_fragment.dir/src/FragmentManager.cpp.o"

# External object files for target tgbot_fragment
tgbot_fragment_EXTERNAL_OBJECTS =

tgbot_fragment/libtgbot_fragment.a: tgbot_fragment/CMakeFiles/tgbot_fragment.dir/src/Fragment.cpp.o
tgbot_fragment/libtgbot_fragment.a: tgbot_fragment/CMakeFiles/tgbot_fragment.dir/src/FragmentManager.cpp.o
tgbot_fragment/libtgbot_fragment.a: tgbot_fragment/CMakeFiles/tgbot_fragment.dir/build.make
tgbot_fragment/libtgbot_fragment.a: tgbot_fragment/CMakeFiles/tgbot_fragment.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anaskhan/proj/botmaestro/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libtgbot_fragment.a"
	cd /home/anaskhan/proj/botmaestro/build/tgbot_fragment && $(CMAKE_COMMAND) -P CMakeFiles/tgbot_fragment.dir/cmake_clean_target.cmake
	cd /home/anaskhan/proj/botmaestro/build/tgbot_fragment && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tgbot_fragment.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tgbot_fragment/CMakeFiles/tgbot_fragment.dir/build: tgbot_fragment/libtgbot_fragment.a
.PHONY : tgbot_fragment/CMakeFiles/tgbot_fragment.dir/build

tgbot_fragment/CMakeFiles/tgbot_fragment.dir/clean:
	cd /home/anaskhan/proj/botmaestro/build/tgbot_fragment && $(CMAKE_COMMAND) -P CMakeFiles/tgbot_fragment.dir/cmake_clean.cmake
.PHONY : tgbot_fragment/CMakeFiles/tgbot_fragment.dir/clean

tgbot_fragment/CMakeFiles/tgbot_fragment.dir/depend:
	cd /home/anaskhan/proj/botmaestro/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anaskhan/proj/botmaestro /home/anaskhan/proj/botmaestro/tgbot_fragment /home/anaskhan/proj/botmaestro/build /home/anaskhan/proj/botmaestro/build/tgbot_fragment /home/anaskhan/proj/botmaestro/build/tgbot_fragment/CMakeFiles/tgbot_fragment.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tgbot_fragment/CMakeFiles/tgbot_fragment.dir/depend

