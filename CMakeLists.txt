cmake_minimum_required(VERSION 2.8)
project(Gold)

set(CMAKE_CXX_STANDARD 11)
#add_compile_options(-std=c++11)

file(GLOB SOURCE "Source/*.cc" "Header/*.h")

add_executable(Gold ${SOURCE})

find_package(Threads REQUIRED)

target_link_libraries(Gold Threads::Threads)