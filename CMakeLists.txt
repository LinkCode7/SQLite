cmake_minimum_required(VERSION 3.19)
project(SQLite)

set(libname "SQLiteModule")

#use C++20 format
set(CMAKE_CXX_STANDARD 20)

file(GLOB SRC
       ${PROJECT_SOURCE_DIR}/*.cpp
       ${PROJECT_SOURCE_DIR}/*.h
       ${PROJECT_SOURCE_DIR}/common/*.cpp
       ${PROJECT_SOURCE_DIR}/common/*.c
       ${PROJECT_SOURCE_DIR}/common/*.h
       ${PROJECT_SOURCE_DIR}/effective/*.cpp
       ${PROJECT_SOURCE_DIR}/effective/*.h
       ${PROJECT_SOURCE_DIR}/sample/*.cpp
       ${PROJECT_SOURCE_DIR}/sample/*.h
       ${PROJECT_SOURCE_DIR}/sample/muParser/*.cpp
       ${PROJECT_SOURCE_DIR}/sample/muParser/*.h
       ${PROJECT_SOURCE_DIR}/sql/*.cpp
       ${PROJECT_SOURCE_DIR}/sql/*.h
       )

#打印SRC中列表信息
message(STATUS "SRC = ${SRC}")

#target_precompile_headers(${PROJECT_NAME} PRIVATE "pch.h")

add_executable(${PROJECT_NAME} ${SRC})
