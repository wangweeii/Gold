cmake_minimum_required(VERSION 3.1.2)
project(Gold)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_LINK_LIBS libmariadb.3.dylib)

link_directories(/Users/vv/lib)

include_directories(mariadb)

add_executable(Gold main.cc)

target_link_libraries(Gold ${PROJECT_LINK_LIBS})
