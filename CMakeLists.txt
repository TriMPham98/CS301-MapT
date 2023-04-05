cmake_minimum_required(VERSION 3.17)
project(MapT_template)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(Map_Example Map_usage_example.cpp MapT.h)