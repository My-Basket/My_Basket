cmake_minimum_required(VERSION 3.17)
project(BUCKET_PROJECT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow  -DLOCAL")
include_directories(include)
add_executable(BUCKET_PROJECT src/main.cpp src/algo.cpp src/view.cpp GUI/recipebook.h GUI/recipebook.cpp GUI/its_qmake_pro_file.h GUI/main_gui.cpp)