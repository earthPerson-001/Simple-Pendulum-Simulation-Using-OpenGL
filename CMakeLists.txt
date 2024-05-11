cmake_minimum_required(VERSION 3.10)

# Required version of cpp
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the project name
project("Simple-Pendulum" VERSION 0.1 LANGUAGES CXX C)

message(STATUS "The build type is set as ${CMAKE_BUILD_TYPE}.")
# set build type as debug
if (NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# create a list to keep source files in a place
set(SRCS "src/main.cpp")

# append lists to add source files
list(APPEND SRCS "src/simple_pendulum.cpp")

if (APPLE)
    # create bundle on apple compiles
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${SRCS} )
else()
    add_executable(${PROJECT_NAME} ${SRCS})
endif()

set(OpenGL_GL_PREFERENCE "LEGACY")

find_package(OpenGL)

set(CPM_USE_LOCAL_PACKAGE TRUE)
include(./cmake/CPM.cmake)

add_subdirectory("./lib")
CPMAddPackage("gh:glfw/glfw#3.4")

target_include_directories("${PROJECT_NAME}" PUBLIC "${PROJECT_BINARY_DIR}" PUBLIC include PUBLIC ${OPENGL_INCLUDE_DIRS})
target_link_libraries("${PROJECT_NAME}" ${OPENGL_LIBRARIES} glfw glad)
