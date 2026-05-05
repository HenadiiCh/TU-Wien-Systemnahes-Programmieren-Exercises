cmake_minimum_required(VERSION 3.20)

# define project metadata

project(exercise2
	LANGUAGES
		CXX
		C
	DESCRIPTION "exercise2"
	HOMEPAGE_URL "https://sgit.iue.tuwien.ac.at/360062/exercise2"
)

# setting required language standard

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

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

# targets & tests

add_executable(task1 src/task1.main.cpp)
add_test(NAME task1 COMMAND task1 WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
set_property(TEST task1 PROPERTY PASS_REGULAR_EXPRESSION "-1024")

add_executable(task2 src/task2.cpp src/task2.test.cpp)
add_test(NAME task2 COMMAND task2 WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

add_executable(task3 src/task3.cpp src/task3.test.cpp)
add_test(NAME task3 COMMAND task3 WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
