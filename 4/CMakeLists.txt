cmake_minimum_required(VERSION 3.20)

# define project metadata

project(exercise4
	LANGUAGES
		CXX
	DESCRIPTION "exercise4"
	HOMEPAGE_URL "https://sgit.iue.tuwien.ac.at/360062/exercise4"
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

include_directories(include)
file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/output)

add_executable(task1 src/task1.main.cpp)
add_test(NAME task1 COMMAND task1 WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
set_property(TEST task1 PROPERTY PASS_REGULAR_EXPRESSION
	"(-112|-1\\.120+e\\+02).*(-211|-2\\.110+e\\+02).*(42|4\\.20+e\\+01).*(-23|-2\\.30+e\\+01)"
)

add_executable(task2 src/task2.cpp src/task2.misc.cpp src/task2.test.cpp)
add_test(NAME task2 COMMAND task2 WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

add_executable(task3 src/task2.cpp src/task2.misc.cpp src/task3.cpp src/task3.misc.cpp src/task3.test.cpp)
add_test(NAME task3 COMMAND task3 WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
