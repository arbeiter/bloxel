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
CMAKE_SOURCE_DIR = /home/pulo/code/graphics/OpenGL/mesh_experiments_opengl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pulo/code/graphics/OpenGL/mesh_experiments_opengl/bin

# Include any dependencies generated for this target.
include CMakeFiles/OpenGLTestApp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/OpenGLTestApp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/OpenGLTestApp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OpenGLTestApp.dir/flags.make

CMakeFiles/OpenGLTestApp.dir/main.cpp.o: CMakeFiles/OpenGLTestApp.dir/flags.make
CMakeFiles/OpenGLTestApp.dir/main.cpp.o: ../main.cpp
CMakeFiles/OpenGLTestApp.dir/main.cpp.o: CMakeFiles/OpenGLTestApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pulo/code/graphics/OpenGL/mesh_experiments_opengl/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/OpenGLTestApp.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OpenGLTestApp.dir/main.cpp.o -MF CMakeFiles/OpenGLTestApp.dir/main.cpp.o.d -o CMakeFiles/OpenGLTestApp.dir/main.cpp.o -c /home/pulo/code/graphics/OpenGL/mesh_experiments_opengl/main.cpp

CMakeFiles/OpenGLTestApp.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenGLTestApp.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pulo/code/graphics/OpenGL/mesh_experiments_opengl/main.cpp > CMakeFiles/OpenGLTestApp.dir/main.cpp.i

CMakeFiles/OpenGLTestApp.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenGLTestApp.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pulo/code/graphics/OpenGL/mesh_experiments_opengl/main.cpp -o CMakeFiles/OpenGLTestApp.dir/main.cpp.s

CMakeFiles/OpenGLTestApp.dir/include/glad/glad.c.o: CMakeFiles/OpenGLTestApp.dir/flags.make
CMakeFiles/OpenGLTestApp.dir/include/glad/glad.c.o: ../include/glad/glad.c
CMakeFiles/OpenGLTestApp.dir/include/glad/glad.c.o: CMakeFiles/OpenGLTestApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pulo/code/graphics/OpenGL/mesh_experiments_opengl/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/OpenGLTestApp.dir/include/glad/glad.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/OpenGLTestApp.dir/include/glad/glad.c.o -MF CMakeFiles/OpenGLTestApp.dir/include/glad/glad.c.o.d -o CMakeFiles/OpenGLTestApp.dir/include/glad/glad.c.o -c /home/pulo/code/graphics/OpenGL/mesh_experiments_opengl/include/glad/glad.c

CMakeFiles/OpenGLTestApp.dir/include/glad/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OpenGLTestApp.dir/include/glad/glad.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pulo/code/graphics/OpenGL/mesh_experiments_opengl/include/glad/glad.c > CMakeFiles/OpenGLTestApp.dir/include/glad/glad.c.i

CMakeFiles/OpenGLTestApp.dir/include/glad/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OpenGLTestApp.dir/include/glad/glad.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pulo/code/graphics/OpenGL/mesh_experiments_opengl/include/glad/glad.c -o CMakeFiles/OpenGLTestApp.dir/include/glad/glad.c.s

# Object files for target OpenGLTestApp
OpenGLTestApp_OBJECTS = \
"CMakeFiles/OpenGLTestApp.dir/main.cpp.o" \
"CMakeFiles/OpenGLTestApp.dir/include/glad/glad.c.o"

# External object files for target OpenGLTestApp
OpenGLTestApp_EXTERNAL_OBJECTS =

OpenGLTestApp: CMakeFiles/OpenGLTestApp.dir/main.cpp.o
OpenGLTestApp: CMakeFiles/OpenGLTestApp.dir/include/glad/glad.c.o
OpenGLTestApp: CMakeFiles/OpenGLTestApp.dir/build.make
OpenGLTestApp: /usr/lib/libglfw.so.3.3
OpenGLTestApp: CMakeFiles/OpenGLTestApp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pulo/code/graphics/OpenGL/mesh_experiments_opengl/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable OpenGLTestApp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OpenGLTestApp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OpenGLTestApp.dir/build: OpenGLTestApp
.PHONY : CMakeFiles/OpenGLTestApp.dir/build

CMakeFiles/OpenGLTestApp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OpenGLTestApp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OpenGLTestApp.dir/clean

CMakeFiles/OpenGLTestApp.dir/depend:
	cd /home/pulo/code/graphics/OpenGL/mesh_experiments_opengl/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pulo/code/graphics/OpenGL/mesh_experiments_opengl /home/pulo/code/graphics/OpenGL/mesh_experiments_opengl /home/pulo/code/graphics/OpenGL/mesh_experiments_opengl/bin /home/pulo/code/graphics/OpenGL/mesh_experiments_opengl/bin /home/pulo/code/graphics/OpenGL/mesh_experiments_opengl/bin/CMakeFiles/OpenGLTestApp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OpenGLTestApp.dir/depend
