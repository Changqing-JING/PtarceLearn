cmake_minimum_required(VERSION 3.5)
project(dummy C ASM)
set(CMAKE_ASM_FLAGS ${CMAKE_ASM_FLAGS} "-g -no-pie -nostdlib")

add_executable(dummy1 dummy1.s)