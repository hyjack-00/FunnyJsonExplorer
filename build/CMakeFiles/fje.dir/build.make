# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.28.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.28.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/hyjack/workspace/SE/FunnyJsonExplorer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/hyjack/workspace/SE/FunnyJsonExplorer/build

# Include any dependencies generated for this target.
include CMakeFiles/fje.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/fje.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/fje.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fje.dir/flags.make

CMakeFiles/fje.dir/src/JsonTree.cpp.o: CMakeFiles/fje.dir/flags.make
CMakeFiles/fje.dir/src/JsonTree.cpp.o: /Users/hyjack/workspace/SE/FunnyJsonExplorer/src/JsonTree.cpp
CMakeFiles/fje.dir/src/JsonTree.cpp.o: CMakeFiles/fje.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/hyjack/workspace/SE/FunnyJsonExplorer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/fje.dir/src/JsonTree.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/fje.dir/src/JsonTree.cpp.o -MF CMakeFiles/fje.dir/src/JsonTree.cpp.o.d -o CMakeFiles/fje.dir/src/JsonTree.cpp.o -c /Users/hyjack/workspace/SE/FunnyJsonExplorer/src/JsonTree.cpp

CMakeFiles/fje.dir/src/JsonTree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/fje.dir/src/JsonTree.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hyjack/workspace/SE/FunnyJsonExplorer/src/JsonTree.cpp > CMakeFiles/fje.dir/src/JsonTree.cpp.i

CMakeFiles/fje.dir/src/JsonTree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/fje.dir/src/JsonTree.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hyjack/workspace/SE/FunnyJsonExplorer/src/JsonTree.cpp -o CMakeFiles/fje.dir/src/JsonTree.cpp.s

CMakeFiles/fje.dir/src/main.cpp.o: CMakeFiles/fje.dir/flags.make
CMakeFiles/fje.dir/src/main.cpp.o: /Users/hyjack/workspace/SE/FunnyJsonExplorer/src/main.cpp
CMakeFiles/fje.dir/src/main.cpp.o: CMakeFiles/fje.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/hyjack/workspace/SE/FunnyJsonExplorer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/fje.dir/src/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/fje.dir/src/main.cpp.o -MF CMakeFiles/fje.dir/src/main.cpp.o.d -o CMakeFiles/fje.dir/src/main.cpp.o -c /Users/hyjack/workspace/SE/FunnyJsonExplorer/src/main.cpp

CMakeFiles/fje.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/fje.dir/src/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hyjack/workspace/SE/FunnyJsonExplorer/src/main.cpp > CMakeFiles/fje.dir/src/main.cpp.i

CMakeFiles/fje.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/fje.dir/src/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hyjack/workspace/SE/FunnyJsonExplorer/src/main.cpp -o CMakeFiles/fje.dir/src/main.cpp.s

# Object files for target fje
fje_OBJECTS = \
"CMakeFiles/fje.dir/src/JsonTree.cpp.o" \
"CMakeFiles/fje.dir/src/main.cpp.o"

# External object files for target fje
fje_EXTERNAL_OBJECTS =

/Users/hyjack/workspace/SE/FunnyJsonExplorer/bin/fje: CMakeFiles/fje.dir/src/JsonTree.cpp.o
/Users/hyjack/workspace/SE/FunnyJsonExplorer/bin/fje: CMakeFiles/fje.dir/src/main.cpp.o
/Users/hyjack/workspace/SE/FunnyJsonExplorer/bin/fje: CMakeFiles/fje.dir/build.make
/Users/hyjack/workspace/SE/FunnyJsonExplorer/bin/fje: CMakeFiles/fje.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/hyjack/workspace/SE/FunnyJsonExplorer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable /Users/hyjack/workspace/SE/FunnyJsonExplorer/bin/fje"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fje.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fje.dir/build: /Users/hyjack/workspace/SE/FunnyJsonExplorer/bin/fje
.PHONY : CMakeFiles/fje.dir/build

CMakeFiles/fje.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fje.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fje.dir/clean

CMakeFiles/fje.dir/depend:
	cd /Users/hyjack/workspace/SE/FunnyJsonExplorer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/hyjack/workspace/SE/FunnyJsonExplorer /Users/hyjack/workspace/SE/FunnyJsonExplorer /Users/hyjack/workspace/SE/FunnyJsonExplorer/build /Users/hyjack/workspace/SE/FunnyJsonExplorer/build /Users/hyjack/workspace/SE/FunnyJsonExplorer/build/CMakeFiles/fje.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/fje.dir/depend

