cmake_minimum_required(VERSION 2.8)
project(Gold)

set(CMAKE_CXX_STANDARD 11)

set(PROJECT_LINK_LIBS libmariadb.so.3)

link_directories(/home/vv/Lib)

include_directories(mariadb)

add_executable(Gold main.cc)

target_link_libraries(Gold ${PROJECT_LINK_LIBS})
