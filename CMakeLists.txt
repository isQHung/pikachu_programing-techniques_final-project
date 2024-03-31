cmake_minimum_required(VERSION 3.9.0)
project(pikachu VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

include_directories()

file(GLOB SOURCES "*.cpp")

add_executable(pikachu ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
