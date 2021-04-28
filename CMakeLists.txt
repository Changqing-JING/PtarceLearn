cmake_minimum_required(VERSION 3.5)
project(PtraceLearn)

aux_source_directory(./src soureFiles)

add_subdirectory(dummy)

add_executable(${PROJECT_NAME} ${soureFiles})