cmake_minimum_required(VERSION 3.16)
project(src C)

set(CMAKE_C_STANDARD 99)

add_executable(src main.c prime.c prime.h hash_table.c hash_table.h)
target_link_libraries(src m) # link the math library