cmake_minimum_required(VERSION 2.8)
project(Gold)
file(GLOB SOURCE "source/*.cc" "header/*.h")
add_executable(Gold ${SOURCE})