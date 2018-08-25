cmake_minimum_required(VERSION 2.8)
project(shit)

set(CMAKE_CXX_STANDARD 11)

set(PROJECT_LINK_LIBS libmariadb.so)

link_directories(/home/vv/Lib)

include_directories(include mariadb)

aux_source_directory(source SOURCE)

add_executable(shit main.cc ${SOURCE})

target_link_libraries(shit ${PROJECT_LINK_LIBS})