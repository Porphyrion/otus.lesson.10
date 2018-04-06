cmake_minimum_required(VERSION 3.5)
project(bulkmt)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads)
find_package(Boost)

include_directories(${Boost_INCLUDE_DIR})

add_library(application application.cpp)
add_library(observer observer.cpp)
add_library(interpreter interpreter.cpp)
add_library(commandblock commandblock.cpp)

add_executable(bulk main.cpp)

target_link_libraries(bulk
    application
    interpreter
    observer
    commandblock
    ${CMAKE_THREAD_LIBS_INIT}
    )
