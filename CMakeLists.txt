cmake_minimum_required(VERSION 3.5)
project(bulkmt VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

set(CMAKE_CXX_STANDARD 14)

find_package(Threads)
find_package(Boost)

include_directories(${Boost_INCLUDE_DIR})

configure_file(version.h.in version.h)

add_library(application application.cpp)
add_library(observer observer.cpp)
add_library(interpreter interpreter.cpp)
add_library(commandblock commandblock.cpp)

add_executable(bulkmt main.cpp)
set_target_properties(bulkmt application interpreter observer commandblock  PROPERTIES
	CXX_STANDARD 14
	CXX_STANDART_REQUIRED ON
	COMPILE_OPTION -Wpedantic -Wall -Wextra
	)
target_link_libraries(bulkmt
    application
    interpreter
    observer
    commandblock
    ${CMAKE_THREAD_LIBS_INIT}
    )

install(TARGETS bulkmt RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT ivanbasurman88@yandex.ru)

include(CPack)
