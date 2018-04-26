cmake_minimum_required(VERSION 3.8)
project(Parser_Generator)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp symbol.cpp non_terminal.h production.h production.cpp symbol.h terminal.cpp
        file_parser.h file_parser.cpp predictive_table.cpp predictive_table.h
        first_follow_wrapper.cpp wrapper.h first_follow_generator.h first_follow_generator.cpp
        headers.h CFG_to_LL1.h CFG_to_LL1.cpp parser.cpp parser.h non_terminal.cpp terminal.h)
add_executable(Parser_Generator ${SOURCE_FILES})