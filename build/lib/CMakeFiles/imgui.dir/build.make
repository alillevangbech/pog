# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_SOURCE_DIR = /home/albec/repos/pog

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/albec/repos/pog/build

# Include any dependencies generated for this target.
include lib/CMakeFiles/imgui.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/CMakeFiles/imgui.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/imgui.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/imgui.dir/flags.make

lib/CMakeFiles/imgui.dir/imgui/imgui.cpp.o: lib/CMakeFiles/imgui.dir/flags.make
lib/CMakeFiles/imgui.dir/imgui/imgui.cpp.o: ../lib/imgui/imgui.cpp
lib/CMakeFiles/imgui.dir/imgui/imgui.cpp.o: lib/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/albec/repos/pog/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/CMakeFiles/imgui.dir/imgui/imgui.cpp.o"
	cd /home/albec/repos/pog/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/CMakeFiles/imgui.dir/imgui/imgui.cpp.o -MF CMakeFiles/imgui.dir/imgui/imgui.cpp.o.d -o CMakeFiles/imgui.dir/imgui/imgui.cpp.o -c /home/albec/repos/pog/lib/imgui/imgui.cpp

lib/CMakeFiles/imgui.dir/imgui/imgui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui/imgui.cpp.i"
	cd /home/albec/repos/pog/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/albec/repos/pog/lib/imgui/imgui.cpp > CMakeFiles/imgui.dir/imgui/imgui.cpp.i

lib/CMakeFiles/imgui.dir/imgui/imgui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui/imgui.cpp.s"
	cd /home/albec/repos/pog/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/albec/repos/pog/lib/imgui/imgui.cpp -o CMakeFiles/imgui.dir/imgui/imgui.cpp.s

lib/CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.o: lib/CMakeFiles/imgui.dir/flags.make
lib/CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.o: ../lib/imgui/imgui_demo.cpp
lib/CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.o: lib/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/albec/repos/pog/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.o"
	cd /home/albec/repos/pog/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.o -MF CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.o.d -o CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.o -c /home/albec/repos/pog/lib/imgui/imgui_demo.cpp

lib/CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.i"
	cd /home/albec/repos/pog/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/albec/repos/pog/lib/imgui/imgui_demo.cpp > CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.i

lib/CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.s"
	cd /home/albec/repos/pog/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/albec/repos/pog/lib/imgui/imgui_demo.cpp -o CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.s

lib/CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.o: lib/CMakeFiles/imgui.dir/flags.make
lib/CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.o: ../lib/imgui/imgui_draw.cpp
lib/CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.o: lib/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/albec/repos/pog/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object lib/CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.o"
	cd /home/albec/repos/pog/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.o -MF CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.o.d -o CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.o -c /home/albec/repos/pog/lib/imgui/imgui_draw.cpp

lib/CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.i"
	cd /home/albec/repos/pog/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/albec/repos/pog/lib/imgui/imgui_draw.cpp > CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.i

lib/CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.s"
	cd /home/albec/repos/pog/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/albec/repos/pog/lib/imgui/imgui_draw.cpp -o CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.s

lib/CMakeFiles/imgui.dir/imgui/imgui_widgets.cpp.o: lib/CMakeFiles/imgui.dir/flags.make
lib/CMakeFiles/imgui.dir/imgui/imgui_widgets.cpp.o: ../lib/imgui/imgui_widgets.cpp
lib/CMakeFiles/imgui.dir/imgui/imgui_widgets.cpp.o: lib/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/albec/repos/pog/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object lib/CMakeFiles/imgui.dir/imgui/imgui_widgets.cpp.o"
	cd /home/albec/repos/pog/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/CMakeFiles/imgui.dir/imgui/imgui_widgets.cpp.o -MF CMakeFiles/imgui.dir/imgui/imgui_widgets.cpp.o.d -o CMakeFiles/imgui.dir/imgui/imgui_widgets.cpp.o -c /home/albec/repos/pog/lib/imgui/imgui_widgets.cpp

lib/CMakeFiles/imgui.dir/imgui/imgui_widgets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui/imgui_widgets.cpp.i"
	cd /home/albec/repos/pog/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/albec/repos/pog/lib/imgui/imgui_widgets.cpp > CMakeFiles/imgui.dir/imgui/imgui_widgets.cpp.i

lib/CMakeFiles/imgui.dir/imgui/imgui_widgets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui/imgui_widgets.cpp.s"
	cd /home/albec/repos/pog/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/albec/repos/pog/lib/imgui/imgui_widgets.cpp -o CMakeFiles/imgui.dir/imgui/imgui_widgets.cpp.s

lib/CMakeFiles/imgui.dir/imgui/imgui_tables.cpp.o: lib/CMakeFiles/imgui.dir/flags.make
lib/CMakeFiles/imgui.dir/imgui/imgui_tables.cpp.o: ../lib/imgui/imgui_tables.cpp
lib/CMakeFiles/imgui.dir/imgui/imgui_tables.cpp.o: lib/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/albec/repos/pog/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object lib/CMakeFiles/imgui.dir/imgui/imgui_tables.cpp.o"
	cd /home/albec/repos/pog/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/CMakeFiles/imgui.dir/imgui/imgui_tables.cpp.o -MF CMakeFiles/imgui.dir/imgui/imgui_tables.cpp.o.d -o CMakeFiles/imgui.dir/imgui/imgui_tables.cpp.o -c /home/albec/repos/pog/lib/imgui/imgui_tables.cpp

lib/CMakeFiles/imgui.dir/imgui/imgui_tables.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui/imgui_tables.cpp.i"
	cd /home/albec/repos/pog/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/albec/repos/pog/lib/imgui/imgui_tables.cpp > CMakeFiles/imgui.dir/imgui/imgui_tables.cpp.i

lib/CMakeFiles/imgui.dir/imgui/imgui_tables.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui/imgui_tables.cpp.s"
	cd /home/albec/repos/pog/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/albec/repos/pog/lib/imgui/imgui_tables.cpp -o CMakeFiles/imgui.dir/imgui/imgui_tables.cpp.s

lib/CMakeFiles/imgui.dir/imgui/backends/imgui_impl_opengl2.cpp.o: lib/CMakeFiles/imgui.dir/flags.make
lib/CMakeFiles/imgui.dir/imgui/backends/imgui_impl_opengl2.cpp.o: ../lib/imgui/backends/imgui_impl_opengl2.cpp
lib/CMakeFiles/imgui.dir/imgui/backends/imgui_impl_opengl2.cpp.o: lib/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/albec/repos/pog/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object lib/CMakeFiles/imgui.dir/imgui/backends/imgui_impl_opengl2.cpp.o"
	cd /home/albec/repos/pog/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/CMakeFiles/imgui.dir/imgui/backends/imgui_impl_opengl2.cpp.o -MF CMakeFiles/imgui.dir/imgui/backends/imgui_impl_opengl2.cpp.o.d -o CMakeFiles/imgui.dir/imgui/backends/imgui_impl_opengl2.cpp.o -c /home/albec/repos/pog/lib/imgui/backends/imgui_impl_opengl2.cpp

lib/CMakeFiles/imgui.dir/imgui/backends/imgui_impl_opengl2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui/backends/imgui_impl_opengl2.cpp.i"
	cd /home/albec/repos/pog/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/albec/repos/pog/lib/imgui/backends/imgui_impl_opengl2.cpp > CMakeFiles/imgui.dir/imgui/backends/imgui_impl_opengl2.cpp.i

lib/CMakeFiles/imgui.dir/imgui/backends/imgui_impl_opengl2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui/backends/imgui_impl_opengl2.cpp.s"
	cd /home/albec/repos/pog/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/albec/repos/pog/lib/imgui/backends/imgui_impl_opengl2.cpp -o CMakeFiles/imgui.dir/imgui/backends/imgui_impl_opengl2.cpp.s

lib/CMakeFiles/imgui.dir/imgui/backends/imgui_impl_glfw.cpp.o: lib/CMakeFiles/imgui.dir/flags.make
lib/CMakeFiles/imgui.dir/imgui/backends/imgui_impl_glfw.cpp.o: ../lib/imgui/backends/imgui_impl_glfw.cpp
lib/CMakeFiles/imgui.dir/imgui/backends/imgui_impl_glfw.cpp.o: lib/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/albec/repos/pog/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object lib/CMakeFiles/imgui.dir/imgui/backends/imgui_impl_glfw.cpp.o"
	cd /home/albec/repos/pog/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/CMakeFiles/imgui.dir/imgui/backends/imgui_impl_glfw.cpp.o -MF CMakeFiles/imgui.dir/imgui/backends/imgui_impl_glfw.cpp.o.d -o CMakeFiles/imgui.dir/imgui/backends/imgui_impl_glfw.cpp.o -c /home/albec/repos/pog/lib/imgui/backends/imgui_impl_glfw.cpp

lib/CMakeFiles/imgui.dir/imgui/backends/imgui_impl_glfw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui/backends/imgui_impl_glfw.cpp.i"
	cd /home/albec/repos/pog/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/albec/repos/pog/lib/imgui/backends/imgui_impl_glfw.cpp > CMakeFiles/imgui.dir/imgui/backends/imgui_impl_glfw.cpp.i

lib/CMakeFiles/imgui.dir/imgui/backends/imgui_impl_glfw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui/backends/imgui_impl_glfw.cpp.s"
	cd /home/albec/repos/pog/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/albec/repos/pog/lib/imgui/backends/imgui_impl_glfw.cpp -o CMakeFiles/imgui.dir/imgui/backends/imgui_impl_glfw.cpp.s

# Object files for target imgui
imgui_OBJECTS = \
"CMakeFiles/imgui.dir/imgui/imgui.cpp.o" \
"CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.o" \
"CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.o" \
"CMakeFiles/imgui.dir/imgui/imgui_widgets.cpp.o" \
"CMakeFiles/imgui.dir/imgui/imgui_tables.cpp.o" \
"CMakeFiles/imgui.dir/imgui/backends/imgui_impl_opengl2.cpp.o" \
"CMakeFiles/imgui.dir/imgui/backends/imgui_impl_glfw.cpp.o"

# External object files for target imgui
imgui_EXTERNAL_OBJECTS =

lib/libimgui.a: lib/CMakeFiles/imgui.dir/imgui/imgui.cpp.o
lib/libimgui.a: lib/CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.o
lib/libimgui.a: lib/CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.o
lib/libimgui.a: lib/CMakeFiles/imgui.dir/imgui/imgui_widgets.cpp.o
lib/libimgui.a: lib/CMakeFiles/imgui.dir/imgui/imgui_tables.cpp.o
lib/libimgui.a: lib/CMakeFiles/imgui.dir/imgui/backends/imgui_impl_opengl2.cpp.o
lib/libimgui.a: lib/CMakeFiles/imgui.dir/imgui/backends/imgui_impl_glfw.cpp.o
lib/libimgui.a: lib/CMakeFiles/imgui.dir/build.make
lib/libimgui.a: lib/CMakeFiles/imgui.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/albec/repos/pog/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX static library libimgui.a"
	cd /home/albec/repos/pog/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/imgui.dir/cmake_clean_target.cmake
	cd /home/albec/repos/pog/build/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/imgui.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/imgui.dir/build: lib/libimgui.a
.PHONY : lib/CMakeFiles/imgui.dir/build

lib/CMakeFiles/imgui.dir/clean:
	cd /home/albec/repos/pog/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/imgui.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/imgui.dir/clean

lib/CMakeFiles/imgui.dir/depend:
	cd /home/albec/repos/pog/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/albec/repos/pog /home/albec/repos/pog/lib /home/albec/repos/pog/build /home/albec/repos/pog/build/lib /home/albec/repos/pog/build/lib/CMakeFiles/imgui.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/imgui.dir/depend

