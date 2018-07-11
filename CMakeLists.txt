cmake_minimum_required(VERSION 2.8)
project(Gold)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCE "Source/*.cc" "Header/*.h")

add_executable(Gold ${SOURCE})