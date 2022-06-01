
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

project ("depends")

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_HOME_DIRECTORY}/out")

add_executable (depends "src/main.cpp" "src/treebuilder.h" "src/treebuilder.cpp")
