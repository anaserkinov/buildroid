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
CMAKE_SOURCE_DIR = /home/anaskhan/proj/buildroid

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anaskhan/proj/buildroid/build

# Include any dependencies generated for this target.
include CMakeFiles/Buildroid.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Buildroid.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Buildroid.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Buildroid.dir/flags.make

CMakeFiles/Buildroid.dir/src/DatabaseController.cpp.o: CMakeFiles/Buildroid.dir/flags.make
CMakeFiles/Buildroid.dir/src/DatabaseController.cpp.o: ../src/DatabaseController.cpp
CMakeFiles/Buildroid.dir/src/DatabaseController.cpp.o: CMakeFiles/Buildroid.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anaskhan/proj/buildroid/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Buildroid.dir/src/DatabaseController.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Buildroid.dir/src/DatabaseController.cpp.o -MF CMakeFiles/Buildroid.dir/src/DatabaseController.cpp.o.d -o CMakeFiles/Buildroid.dir/src/DatabaseController.cpp.o -c /home/anaskhan/proj/buildroid/src/DatabaseController.cpp

CMakeFiles/Buildroid.dir/src/DatabaseController.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Buildroid.dir/src/DatabaseController.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anaskhan/proj/buildroid/src/DatabaseController.cpp > CMakeFiles/Buildroid.dir/src/DatabaseController.cpp.i

CMakeFiles/Buildroid.dir/src/DatabaseController.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Buildroid.dir/src/DatabaseController.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anaskhan/proj/buildroid/src/DatabaseController.cpp -o CMakeFiles/Buildroid.dir/src/DatabaseController.cpp.s

CMakeFiles/Buildroid.dir/src/GitManager.cpp.o: CMakeFiles/Buildroid.dir/flags.make
CMakeFiles/Buildroid.dir/src/GitManager.cpp.o: ../src/GitManager.cpp
CMakeFiles/Buildroid.dir/src/GitManager.cpp.o: CMakeFiles/Buildroid.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anaskhan/proj/buildroid/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Buildroid.dir/src/GitManager.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Buildroid.dir/src/GitManager.cpp.o -MF CMakeFiles/Buildroid.dir/src/GitManager.cpp.o.d -o CMakeFiles/Buildroid.dir/src/GitManager.cpp.o -c /home/anaskhan/proj/buildroid/src/GitManager.cpp

CMakeFiles/Buildroid.dir/src/GitManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Buildroid.dir/src/GitManager.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anaskhan/proj/buildroid/src/GitManager.cpp > CMakeFiles/Buildroid.dir/src/GitManager.cpp.i

CMakeFiles/Buildroid.dir/src/GitManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Buildroid.dir/src/GitManager.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anaskhan/proj/buildroid/src/GitManager.cpp -o CMakeFiles/Buildroid.dir/src/GitManager.cpp.s

CMakeFiles/Buildroid.dir/src/Main.cpp.o: CMakeFiles/Buildroid.dir/flags.make
CMakeFiles/Buildroid.dir/src/Main.cpp.o: ../src/Main.cpp
CMakeFiles/Buildroid.dir/src/Main.cpp.o: CMakeFiles/Buildroid.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anaskhan/proj/buildroid/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Buildroid.dir/src/Main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Buildroid.dir/src/Main.cpp.o -MF CMakeFiles/Buildroid.dir/src/Main.cpp.o.d -o CMakeFiles/Buildroid.dir/src/Main.cpp.o -c /home/anaskhan/proj/buildroid/src/Main.cpp

CMakeFiles/Buildroid.dir/src/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Buildroid.dir/src/Main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anaskhan/proj/buildroid/src/Main.cpp > CMakeFiles/Buildroid.dir/src/Main.cpp.i

CMakeFiles/Buildroid.dir/src/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Buildroid.dir/src/Main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anaskhan/proj/buildroid/src/Main.cpp -o CMakeFiles/Buildroid.dir/src/Main.cpp.s

CMakeFiles/Buildroid.dir/src/MainDatabase.cpp.o: CMakeFiles/Buildroid.dir/flags.make
CMakeFiles/Buildroid.dir/src/MainDatabase.cpp.o: ../src/MainDatabase.cpp
CMakeFiles/Buildroid.dir/src/MainDatabase.cpp.o: CMakeFiles/Buildroid.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anaskhan/proj/buildroid/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Buildroid.dir/src/MainDatabase.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Buildroid.dir/src/MainDatabase.cpp.o -MF CMakeFiles/Buildroid.dir/src/MainDatabase.cpp.o.d -o CMakeFiles/Buildroid.dir/src/MainDatabase.cpp.o -c /home/anaskhan/proj/buildroid/src/MainDatabase.cpp

CMakeFiles/Buildroid.dir/src/MainDatabase.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Buildroid.dir/src/MainDatabase.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anaskhan/proj/buildroid/src/MainDatabase.cpp > CMakeFiles/Buildroid.dir/src/MainDatabase.cpp.i

CMakeFiles/Buildroid.dir/src/MainDatabase.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Buildroid.dir/src/MainDatabase.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anaskhan/proj/buildroid/src/MainDatabase.cpp -o CMakeFiles/Buildroid.dir/src/MainDatabase.cpp.s

CMakeFiles/Buildroid.dir/src/fragments/AppFragment.cpp.o: CMakeFiles/Buildroid.dir/flags.make
CMakeFiles/Buildroid.dir/src/fragments/AppFragment.cpp.o: ../src/fragments/AppFragment.cpp
CMakeFiles/Buildroid.dir/src/fragments/AppFragment.cpp.o: CMakeFiles/Buildroid.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anaskhan/proj/buildroid/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Buildroid.dir/src/fragments/AppFragment.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Buildroid.dir/src/fragments/AppFragment.cpp.o -MF CMakeFiles/Buildroid.dir/src/fragments/AppFragment.cpp.o.d -o CMakeFiles/Buildroid.dir/src/fragments/AppFragment.cpp.o -c /home/anaskhan/proj/buildroid/src/fragments/AppFragment.cpp

CMakeFiles/Buildroid.dir/src/fragments/AppFragment.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Buildroid.dir/src/fragments/AppFragment.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anaskhan/proj/buildroid/src/fragments/AppFragment.cpp > CMakeFiles/Buildroid.dir/src/fragments/AppFragment.cpp.i

CMakeFiles/Buildroid.dir/src/fragments/AppFragment.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Buildroid.dir/src/fragments/AppFragment.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anaskhan/proj/buildroid/src/fragments/AppFragment.cpp -o CMakeFiles/Buildroid.dir/src/fragments/AppFragment.cpp.s

CMakeFiles/Buildroid.dir/src/fragments/BaseFragment.cpp.o: CMakeFiles/Buildroid.dir/flags.make
CMakeFiles/Buildroid.dir/src/fragments/BaseFragment.cpp.o: ../src/fragments/BaseFragment.cpp
CMakeFiles/Buildroid.dir/src/fragments/BaseFragment.cpp.o: CMakeFiles/Buildroid.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anaskhan/proj/buildroid/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Buildroid.dir/src/fragments/BaseFragment.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Buildroid.dir/src/fragments/BaseFragment.cpp.o -MF CMakeFiles/Buildroid.dir/src/fragments/BaseFragment.cpp.o.d -o CMakeFiles/Buildroid.dir/src/fragments/BaseFragment.cpp.o -c /home/anaskhan/proj/buildroid/src/fragments/BaseFragment.cpp

CMakeFiles/Buildroid.dir/src/fragments/BaseFragment.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Buildroid.dir/src/fragments/BaseFragment.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anaskhan/proj/buildroid/src/fragments/BaseFragment.cpp > CMakeFiles/Buildroid.dir/src/fragments/BaseFragment.cpp.i

CMakeFiles/Buildroid.dir/src/fragments/BaseFragment.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Buildroid.dir/src/fragments/BaseFragment.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anaskhan/proj/buildroid/src/fragments/BaseFragment.cpp -o CMakeFiles/Buildroid.dir/src/fragments/BaseFragment.cpp.s

CMakeFiles/Buildroid.dir/src/fragments/BuildTypeFragment.cpp.o: CMakeFiles/Buildroid.dir/flags.make
CMakeFiles/Buildroid.dir/src/fragments/BuildTypeFragment.cpp.o: ../src/fragments/BuildTypeFragment.cpp
CMakeFiles/Buildroid.dir/src/fragments/BuildTypeFragment.cpp.o: CMakeFiles/Buildroid.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anaskhan/proj/buildroid/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Buildroid.dir/src/fragments/BuildTypeFragment.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Buildroid.dir/src/fragments/BuildTypeFragment.cpp.o -MF CMakeFiles/Buildroid.dir/src/fragments/BuildTypeFragment.cpp.o.d -o CMakeFiles/Buildroid.dir/src/fragments/BuildTypeFragment.cpp.o -c /home/anaskhan/proj/buildroid/src/fragments/BuildTypeFragment.cpp

CMakeFiles/Buildroid.dir/src/fragments/BuildTypeFragment.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Buildroid.dir/src/fragments/BuildTypeFragment.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anaskhan/proj/buildroid/src/fragments/BuildTypeFragment.cpp > CMakeFiles/Buildroid.dir/src/fragments/BuildTypeFragment.cpp.i

CMakeFiles/Buildroid.dir/src/fragments/BuildTypeFragment.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Buildroid.dir/src/fragments/BuildTypeFragment.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anaskhan/proj/buildroid/src/fragments/BuildTypeFragment.cpp -o CMakeFiles/Buildroid.dir/src/fragments/BuildTypeFragment.cpp.s

CMakeFiles/Buildroid.dir/src/fragments/ConfirmFragment.cpp.o: CMakeFiles/Buildroid.dir/flags.make
CMakeFiles/Buildroid.dir/src/fragments/ConfirmFragment.cpp.o: ../src/fragments/ConfirmFragment.cpp
CMakeFiles/Buildroid.dir/src/fragments/ConfirmFragment.cpp.o: CMakeFiles/Buildroid.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anaskhan/proj/buildroid/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Buildroid.dir/src/fragments/ConfirmFragment.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Buildroid.dir/src/fragments/ConfirmFragment.cpp.o -MF CMakeFiles/Buildroid.dir/src/fragments/ConfirmFragment.cpp.o.d -o CMakeFiles/Buildroid.dir/src/fragments/ConfirmFragment.cpp.o -c /home/anaskhan/proj/buildroid/src/fragments/ConfirmFragment.cpp

CMakeFiles/Buildroid.dir/src/fragments/ConfirmFragment.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Buildroid.dir/src/fragments/ConfirmFragment.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anaskhan/proj/buildroid/src/fragments/ConfirmFragment.cpp > CMakeFiles/Buildroid.dir/src/fragments/ConfirmFragment.cpp.i

CMakeFiles/Buildroid.dir/src/fragments/ConfirmFragment.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Buildroid.dir/src/fragments/ConfirmFragment.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anaskhan/proj/buildroid/src/fragments/ConfirmFragment.cpp -o CMakeFiles/Buildroid.dir/src/fragments/ConfirmFragment.cpp.s

CMakeFiles/Buildroid.dir/src/fragments/LoginFragment.cpp.o: CMakeFiles/Buildroid.dir/flags.make
CMakeFiles/Buildroid.dir/src/fragments/LoginFragment.cpp.o: ../src/fragments/LoginFragment.cpp
CMakeFiles/Buildroid.dir/src/fragments/LoginFragment.cpp.o: CMakeFiles/Buildroid.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anaskhan/proj/buildroid/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/Buildroid.dir/src/fragments/LoginFragment.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Buildroid.dir/src/fragments/LoginFragment.cpp.o -MF CMakeFiles/Buildroid.dir/src/fragments/LoginFragment.cpp.o.d -o CMakeFiles/Buildroid.dir/src/fragments/LoginFragment.cpp.o -c /home/anaskhan/proj/buildroid/src/fragments/LoginFragment.cpp

CMakeFiles/Buildroid.dir/src/fragments/LoginFragment.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Buildroid.dir/src/fragments/LoginFragment.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anaskhan/proj/buildroid/src/fragments/LoginFragment.cpp > CMakeFiles/Buildroid.dir/src/fragments/LoginFragment.cpp.i

CMakeFiles/Buildroid.dir/src/fragments/LoginFragment.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Buildroid.dir/src/fragments/LoginFragment.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anaskhan/proj/buildroid/src/fragments/LoginFragment.cpp -o CMakeFiles/Buildroid.dir/src/fragments/LoginFragment.cpp.s

CMakeFiles/Buildroid.dir/src/fragments/MainFragment.cpp.o: CMakeFiles/Buildroid.dir/flags.make
CMakeFiles/Buildroid.dir/src/fragments/MainFragment.cpp.o: ../src/fragments/MainFragment.cpp
CMakeFiles/Buildroid.dir/src/fragments/MainFragment.cpp.o: CMakeFiles/Buildroid.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anaskhan/proj/buildroid/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/Buildroid.dir/src/fragments/MainFragment.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Buildroid.dir/src/fragments/MainFragment.cpp.o -MF CMakeFiles/Buildroid.dir/src/fragments/MainFragment.cpp.o.d -o CMakeFiles/Buildroid.dir/src/fragments/MainFragment.cpp.o -c /home/anaskhan/proj/buildroid/src/fragments/MainFragment.cpp

CMakeFiles/Buildroid.dir/src/fragments/MainFragment.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Buildroid.dir/src/fragments/MainFragment.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anaskhan/proj/buildroid/src/fragments/MainFragment.cpp > CMakeFiles/Buildroid.dir/src/fragments/MainFragment.cpp.i

CMakeFiles/Buildroid.dir/src/fragments/MainFragment.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Buildroid.dir/src/fragments/MainFragment.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anaskhan/proj/buildroid/src/fragments/MainFragment.cpp -o CMakeFiles/Buildroid.dir/src/fragments/MainFragment.cpp.s

CMakeFiles/Buildroid.dir/src/fragments/TaxiFragment.cpp.o: CMakeFiles/Buildroid.dir/flags.make
CMakeFiles/Buildroid.dir/src/fragments/TaxiFragment.cpp.o: ../src/fragments/TaxiFragment.cpp
CMakeFiles/Buildroid.dir/src/fragments/TaxiFragment.cpp.o: CMakeFiles/Buildroid.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anaskhan/proj/buildroid/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/Buildroid.dir/src/fragments/TaxiFragment.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Buildroid.dir/src/fragments/TaxiFragment.cpp.o -MF CMakeFiles/Buildroid.dir/src/fragments/TaxiFragment.cpp.o.d -o CMakeFiles/Buildroid.dir/src/fragments/TaxiFragment.cpp.o -c /home/anaskhan/proj/buildroid/src/fragments/TaxiFragment.cpp

CMakeFiles/Buildroid.dir/src/fragments/TaxiFragment.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Buildroid.dir/src/fragments/TaxiFragment.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anaskhan/proj/buildroid/src/fragments/TaxiFragment.cpp > CMakeFiles/Buildroid.dir/src/fragments/TaxiFragment.cpp.i

CMakeFiles/Buildroid.dir/src/fragments/TaxiFragment.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Buildroid.dir/src/fragments/TaxiFragment.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anaskhan/proj/buildroid/src/fragments/TaxiFragment.cpp -o CMakeFiles/Buildroid.dir/src/fragments/TaxiFragment.cpp.s

CMakeFiles/Buildroid.dir/src/tgbot_fragment_db_impl/FragmentStateController.cpp.o: CMakeFiles/Buildroid.dir/flags.make
CMakeFiles/Buildroid.dir/src/tgbot_fragment_db_impl/FragmentStateController.cpp.o: ../src/tgbot_fragment_db_impl/FragmentStateController.cpp
CMakeFiles/Buildroid.dir/src/tgbot_fragment_db_impl/FragmentStateController.cpp.o: CMakeFiles/Buildroid.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anaskhan/proj/buildroid/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/Buildroid.dir/src/tgbot_fragment_db_impl/FragmentStateController.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Buildroid.dir/src/tgbot_fragment_db_impl/FragmentStateController.cpp.o -MF CMakeFiles/Buildroid.dir/src/tgbot_fragment_db_impl/FragmentStateController.cpp.o.d -o CMakeFiles/Buildroid.dir/src/tgbot_fragment_db_impl/FragmentStateController.cpp.o -c /home/anaskhan/proj/buildroid/src/tgbot_fragment_db_impl/FragmentStateController.cpp

CMakeFiles/Buildroid.dir/src/tgbot_fragment_db_impl/FragmentStateController.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Buildroid.dir/src/tgbot_fragment_db_impl/FragmentStateController.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anaskhan/proj/buildroid/src/tgbot_fragment_db_impl/FragmentStateController.cpp > CMakeFiles/Buildroid.dir/src/tgbot_fragment_db_impl/FragmentStateController.cpp.i

CMakeFiles/Buildroid.dir/src/tgbot_fragment_db_impl/FragmentStateController.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Buildroid.dir/src/tgbot_fragment_db_impl/FragmentStateController.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anaskhan/proj/buildroid/src/tgbot_fragment_db_impl/FragmentStateController.cpp -o CMakeFiles/Buildroid.dir/src/tgbot_fragment_db_impl/FragmentStateController.cpp.s

CMakeFiles/Buildroid.dir/src/utils.cpp.o: CMakeFiles/Buildroid.dir/flags.make
CMakeFiles/Buildroid.dir/src/utils.cpp.o: ../src/utils.cpp
CMakeFiles/Buildroid.dir/src/utils.cpp.o: CMakeFiles/Buildroid.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anaskhan/proj/buildroid/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/Buildroid.dir/src/utils.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Buildroid.dir/src/utils.cpp.o -MF CMakeFiles/Buildroid.dir/src/utils.cpp.o.d -o CMakeFiles/Buildroid.dir/src/utils.cpp.o -c /home/anaskhan/proj/buildroid/src/utils.cpp

CMakeFiles/Buildroid.dir/src/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Buildroid.dir/src/utils.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anaskhan/proj/buildroid/src/utils.cpp > CMakeFiles/Buildroid.dir/src/utils.cpp.i

CMakeFiles/Buildroid.dir/src/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Buildroid.dir/src/utils.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anaskhan/proj/buildroid/src/utils.cpp -o CMakeFiles/Buildroid.dir/src/utils.cpp.s

# Object files for target Buildroid
Buildroid_OBJECTS = \
"CMakeFiles/Buildroid.dir/src/DatabaseController.cpp.o" \
"CMakeFiles/Buildroid.dir/src/GitManager.cpp.o" \
"CMakeFiles/Buildroid.dir/src/Main.cpp.o" \
"CMakeFiles/Buildroid.dir/src/MainDatabase.cpp.o" \
"CMakeFiles/Buildroid.dir/src/fragments/AppFragment.cpp.o" \
"CMakeFiles/Buildroid.dir/src/fragments/BaseFragment.cpp.o" \
"CMakeFiles/Buildroid.dir/src/fragments/BuildTypeFragment.cpp.o" \
"CMakeFiles/Buildroid.dir/src/fragments/ConfirmFragment.cpp.o" \
"CMakeFiles/Buildroid.dir/src/fragments/LoginFragment.cpp.o" \
"CMakeFiles/Buildroid.dir/src/fragments/MainFragment.cpp.o" \
"CMakeFiles/Buildroid.dir/src/fragments/TaxiFragment.cpp.o" \
"CMakeFiles/Buildroid.dir/src/tgbot_fragment_db_impl/FragmentStateController.cpp.o" \
"CMakeFiles/Buildroid.dir/src/utils.cpp.o"

# External object files for target Buildroid
Buildroid_EXTERNAL_OBJECTS =

Buildroid: CMakeFiles/Buildroid.dir/src/DatabaseController.cpp.o
Buildroid: CMakeFiles/Buildroid.dir/src/GitManager.cpp.o
Buildroid: CMakeFiles/Buildroid.dir/src/Main.cpp.o
Buildroid: CMakeFiles/Buildroid.dir/src/MainDatabase.cpp.o
Buildroid: CMakeFiles/Buildroid.dir/src/fragments/AppFragment.cpp.o
Buildroid: CMakeFiles/Buildroid.dir/src/fragments/BaseFragment.cpp.o
Buildroid: CMakeFiles/Buildroid.dir/src/fragments/BuildTypeFragment.cpp.o
Buildroid: CMakeFiles/Buildroid.dir/src/fragments/ConfirmFragment.cpp.o
Buildroid: CMakeFiles/Buildroid.dir/src/fragments/LoginFragment.cpp.o
Buildroid: CMakeFiles/Buildroid.dir/src/fragments/MainFragment.cpp.o
Buildroid: CMakeFiles/Buildroid.dir/src/fragments/TaxiFragment.cpp.o
Buildroid: CMakeFiles/Buildroid.dir/src/tgbot_fragment_db_impl/FragmentStateController.cpp.o
Buildroid: CMakeFiles/Buildroid.dir/src/utils.cpp.o
Buildroid: CMakeFiles/Buildroid.dir/build.make
Buildroid: tgbot_fragment/libtgbot_fragment.a
Buildroid: sqlite_cpp/libsqlite_cpp.a
Buildroid: tgbot_fragment/tgbot-cpp/libTgBot.a
Buildroid: /usr/local/lib/libcpprest.so.2.10
Buildroid: libgit2/libgit2.a
Buildroid: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.74.0
Buildroid: /usr/local/lib/libcurl.so
Buildroid: /usr/local/lib/libz.so
Buildroid: /usr/lib/x86_64-linux-gnu/libssl.so
Buildroid: /usr/lib/x86_64-linux-gnu/libcrypto.so
Buildroid: CMakeFiles/Buildroid.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anaskhan/proj/buildroid/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking CXX executable Buildroid"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Buildroid.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Buildroid.dir/build: Buildroid
.PHONY : CMakeFiles/Buildroid.dir/build

CMakeFiles/Buildroid.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Buildroid.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Buildroid.dir/clean

CMakeFiles/Buildroid.dir/depend:
	cd /home/anaskhan/proj/buildroid/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anaskhan/proj/buildroid /home/anaskhan/proj/buildroid /home/anaskhan/proj/buildroid/build /home/anaskhan/proj/buildroid/build /home/anaskhan/proj/buildroid/build/CMakeFiles/Buildroid.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Buildroid.dir/depend

