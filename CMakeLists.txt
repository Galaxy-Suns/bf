cmake_minimum_required(VERSION 3.12)
project(bf
    VERSION 0.2.0
    LANGUAGES CXX
)

find_package(termcolor CONFIG REQUIRED)
add_executable(bf
    src/bf.cpp
    src/main.cpp
)
target_link_libraries(bf PRIVATE termcolor::termcolor)
