cmake_minimum_required(VERSION 3.20)

# define project metadata

project(exercise1
	LANGUAGES
		CXX
		C
	DESCRIPTION "exercise1"
	HOMEPAGE_URL "https://sgit.iue.tuwien.ac.at/360062/exercise1"
)

# setting required language standard

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_EXTENSIONS OFF)

# misc settings

## avoid ctest dashboard targets
set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1)
## make all symbols visible on windows (which is default on unix)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
## generate a compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
## https://gitlab.kitware.com/cmake/cmake/-/issues/20912
set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES
	${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES}
)

# enable CTest

include(CTest)
enable_testing()

# dependencies

find_package(Python3 COMPONENTS Interpreter REQUIRED)

# targets & tests

file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/output)

add_test(
	NAME task1py
	COMMAND ${Python3_EXECUTABLE} src/task1.test.py
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_executable(task1c src/task1.test.c)
add_test(NAME task1c COMMAND task1c WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

add_executable(task1cpp src/task1.test.cpp)
add_test(
	NAME task1cpp
	COMMAND task1cpp
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_executable(task2 src/task2.main.cpp)
add_test(NAME task2 COMMAND task2 WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
set_property(TEST task2 PROPERTY PASS_REGULAR_EXPRESSION "6633")

add_executable(task3 src/task3.cpp src/task3.test.cpp)
add_test(NAME task3 COMMAND task3 WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
