# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/bruno/Desktop/td

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bruno/Desktop/td/build

# Include any dependencies generated for this target.
include CMakeFiles/td.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/td.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/td.dir/flags.make

CMakeFiles/td.dir/td.cpp.o: CMakeFiles/td.dir/flags.make
CMakeFiles/td.dir/td.cpp.o: ../td.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bruno/Desktop/td/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/td.dir/td.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/td.dir/td.cpp.o -c /home/bruno/Desktop/td/td.cpp

CMakeFiles/td.dir/td.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/td.dir/td.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/bruno/Desktop/td/td.cpp > CMakeFiles/td.dir/td.cpp.i

CMakeFiles/td.dir/td.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/td.dir/td.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/bruno/Desktop/td/td.cpp -o CMakeFiles/td.dir/td.cpp.s

CMakeFiles/td.dir/td.cpp.o.requires:
.PHONY : CMakeFiles/td.dir/td.cpp.o.requires

CMakeFiles/td.dir/td.cpp.o.provides: CMakeFiles/td.dir/td.cpp.o.requires
	$(MAKE) -f CMakeFiles/td.dir/build.make CMakeFiles/td.dir/td.cpp.o.provides.build
.PHONY : CMakeFiles/td.dir/td.cpp.o.provides

CMakeFiles/td.dir/td.cpp.o.provides.build: CMakeFiles/td.dir/td.cpp.o

# Object files for target td
td_OBJECTS = \
"CMakeFiles/td.dir/td.cpp.o"

# External object files for target td
td_EXTERNAL_OBJECTS =

td: CMakeFiles/td.dir/td.cpp.o
td: CMakeFiles/td.dir/build.make
td: /usr/local/lib/libopencv_videostab.so.3.0.0
td: /usr/local/lib/libopencv_videoio.so.3.0.0
td: /usr/local/lib/libopencv_video.so.3.0.0
td: /usr/local/lib/libopencv_superres.so.3.0.0
td: /usr/local/lib/libopencv_stitching.so.3.0.0
td: /usr/local/lib/libopencv_shape.so.3.0.0
td: /usr/local/lib/libopencv_photo.so.3.0.0
td: /usr/local/lib/libopencv_objdetect.so.3.0.0
td: /usr/local/lib/libopencv_ml.so.3.0.0
td: /usr/local/lib/libopencv_imgproc.so.3.0.0
td: /usr/local/lib/libopencv_imgcodecs.so.3.0.0
td: /usr/local/lib/libopencv_highgui.so.3.0.0
td: /usr/local/lib/libopencv_hal.a
td: /usr/local/lib/libopencv_flann.so.3.0.0
td: /usr/local/lib/libopencv_features2d.so.3.0.0
td: /usr/local/lib/libopencv_core.so.3.0.0
td: /usr/local/lib/libopencv_calib3d.so.3.0.0
td: /usr/local/lib/libfreenect2.so
td: /usr/local/lib/libopencv_features2d.so.3.0.0
td: /usr/local/lib/libopencv_ml.so.3.0.0
td: /usr/local/lib/libopencv_highgui.so.3.0.0
td: /usr/local/lib/libopencv_videoio.so.3.0.0
td: /usr/local/lib/libopencv_imgcodecs.so.3.0.0
td: /usr/local/lib/libopencv_flann.so.3.0.0
td: /usr/local/lib/libopencv_video.so.3.0.0
td: /usr/local/lib/libopencv_imgproc.so.3.0.0
td: /usr/local/lib/libopencv_core.so.3.0.0
td: /usr/local/lib/libopencv_hal.a
td: /usr/local/share/OpenCV/3rdparty/lib/libippicv.a
td: CMakeFiles/td.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable td"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/td.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/td.dir/build: td
.PHONY : CMakeFiles/td.dir/build

CMakeFiles/td.dir/requires: CMakeFiles/td.dir/td.cpp.o.requires
.PHONY : CMakeFiles/td.dir/requires

CMakeFiles/td.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/td.dir/cmake_clean.cmake
.PHONY : CMakeFiles/td.dir/clean

CMakeFiles/td.dir/depend:
	cd /home/bruno/Desktop/td/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bruno/Desktop/td /home/bruno/Desktop/td /home/bruno/Desktop/td/build /home/bruno/Desktop/td/build /home/bruno/Desktop/td/build/CMakeFiles/td.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/td.dir/depend
