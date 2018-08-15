cmake_minimum_required(VERSION 3.1.2)
project(Gold)

set(CMAKE_CXX_STANDARD 14)

include_directories(mariadb)

#MacOS
#link_directories(/Users/vv/lib)
#set(PROJECT_LINK_LIBS libmariadb.3.dylib)
#add_executable(Gold main.cc)
#target_link_libraries(Gold ${PROJECT_LINK_LIBS})

#Windows
set(PROJECT_LINK_LIBS libmariadb.dll)
link_directories(c:/lib)
add_executable(Gold main.cc)
target_link_libraries(Gold ${PROJECT_LINK_LIBS})
