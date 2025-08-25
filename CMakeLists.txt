cmake_minimum_required(VERSION 3.12)
project(bf
    VERSION 0.5.0
    LANGUAGES CXX
)

add_executable(bf
    src/bf.cpp
    src/main.cpp
    src/Options.cpp
    src/UTF8.cpp
)
target_include_directories(bf PRIVATE external)

include(GNUInstallDirs)
install(TARGETS bf DESTINATION ${CMAKE_INSTALL_BINDIR})
