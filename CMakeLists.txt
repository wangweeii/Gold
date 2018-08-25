cmake_minimum_required(VERSION 2.8)
project(Gold)

set(CMAKE_CXX_STANDARD 11)

set(PROJECT_LINK_LIBS libmariadb.so)

link_directories(/home/vv/Lib)

include_directories(mariadb)

include_directories(include)

aux_source_directory(source SOURCE)

add_executable(Gold main.cc ${SOURCE})

target_link_libraries(Gold ${PROJECT_LINK_LIBS})
