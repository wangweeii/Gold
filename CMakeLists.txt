cmake_minimum_required(VERSION 2.8)
project(Gold)

set(CMAKE_CXX_STANDARD 14)
#add_compile_options(-std=c++11)

#set(PROJECT_LINK_LIBS libhello.a)
#link_directories(/Users/vv/lib)

include_directories(include)

file(GLOB SOURCE "source/*.cc")

add_executable(Gold ${SOURCE})

target_link_libraries(Gold Threads::Threads)# ${PROJECT_LINK_LIBS} ${PYTHON_LIBRARIES})

find_package(Threads REQUIRED)
