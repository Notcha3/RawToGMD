cmake_minimum_required(VERSION 3.6.0)
project("rawtogmd")
add_executable(${PROJECT_NAME} "main.c" "main.h")
target_compile_options(${PROJECT_NAME} PUBLIC -std=c99 -O2)