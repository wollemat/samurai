cmake_minimum_required(VERSION 3.15)
project(Samurai)

set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(samurai src/main.c)