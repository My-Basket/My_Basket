cmake_minimum_required(VERSION 3.17)
project(json_utility)

set(CMAKE_CXX_STANDARD 17)

include_directories(../include)
add_executable(json_utility ../src/search_engine.cpp ../src/work_with_string.cpp json_utility.cpp)