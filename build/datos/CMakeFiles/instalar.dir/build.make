# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jfonseca/GitHub/Annealing

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jfonseca/GitHub/Annealing/build

# Utility rule file for instalar.

# Include the progress variables for this target.
include datos/CMakeFiles/instalar.dir/progress.make

datos/CMakeFiles/instalar: ../datos/SA.param
datos/CMakeFiles/instalar: ../datos/Anclas.txt
datos/CMakeFiles/instalar: ../datos/Allposition.txt
datos/CMakeFiles/instalar: ../datos/Matriz1.txt
datos/CMakeFiles/instalar: ../datos/Matriz2.txt
datos/CMakeFiles/instalar: ../datos/Matriz3.txt
datos/CMakeFiles/instalar: ../datos/Matriz4.txt
datos/CMakeFiles/instalar: ../datos


instalar: datos/CMakeFiles/instalar
instalar: datos/CMakeFiles/instalar.dir/build.make
	cd /home/jfonseca/GitHub/Annealing/build/datos && /usr/bin/cmake -E copy_if_different /home/jfonseca/GitHub/Annealing/datos/SA.param /home/jfonseca/GitHub/Annealing/build/application
	cd /home/jfonseca/GitHub/Annealing/build/datos && /usr/bin/cmake -E copy_if_different /home/jfonseca/GitHub/Annealing/datos/Anclas.txt /home/jfonseca/GitHub/Annealing/build/application
	cd /home/jfonseca/GitHub/Annealing/build/datos && /usr/bin/cmake -E copy_if_different /home/jfonseca/GitHub/Annealing/datos/Allposition.txt /home/jfonseca/GitHub/Annealing/build/application
	cd /home/jfonseca/GitHub/Annealing/build/datos && /usr/bin/cmake -E copy_if_different /home/jfonseca/GitHub/Annealing/datos/Matriz1.txt /home/jfonseca/GitHub/Annealing/build/application
	cd /home/jfonseca/GitHub/Annealing/build/datos && /usr/bin/cmake -E copy_if_different /home/jfonseca/GitHub/Annealing/datos/Matriz2.txt /home/jfonseca/GitHub/Annealing/build/application
	cd /home/jfonseca/GitHub/Annealing/build/datos && /usr/bin/cmake -E copy_if_different /home/jfonseca/GitHub/Annealing/datos/Matriz3.txt /home/jfonseca/GitHub/Annealing/build/application
	cd /home/jfonseca/GitHub/Annealing/build/datos && /usr/bin/cmake -E copy_if_different /home/jfonseca/GitHub/Annealing/datos/Matriz4.txt /home/jfonseca/GitHub/Annealing/build/application
	cd /home/jfonseca/GitHub/Annealing/build/datos && /usr/bin/cmake
.PHONY : instalar

# Rule to build all files generated by this target.
datos/CMakeFiles/instalar.dir/build: instalar

.PHONY : datos/CMakeFiles/instalar.dir/build

datos/CMakeFiles/instalar.dir/clean:
	cd /home/jfonseca/GitHub/Annealing/build/datos && $(CMAKE_COMMAND) -P CMakeFiles/instalar.dir/cmake_clean.cmake
.PHONY : datos/CMakeFiles/instalar.dir/clean

datos/CMakeFiles/instalar.dir/depend:
	cd /home/jfonseca/GitHub/Annealing/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jfonseca/GitHub/Annealing /home/jfonseca/GitHub/Annealing/datos /home/jfonseca/GitHub/Annealing/build /home/jfonseca/GitHub/Annealing/build/datos /home/jfonseca/GitHub/Annealing/build/datos/CMakeFiles/instalar.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : datos/CMakeFiles/instalar.dir/depend

