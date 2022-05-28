# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

# Добавьте источник в исполняемый файл этого проекта.

project ("depends")

# Включите подпроекты.
add_executable (depends "src/main.cpp" "src/treebuilder.h" "src/treebuilder.cpp")
