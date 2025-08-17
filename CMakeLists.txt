cmake_minimum_required(VERSION 3.12)
project(bf
    VERSION 0.3.1
    LANGUAGES CXX
)

find_package(termcolor CONFIG REQUIRED)
add_executable(bf
    src/bf.cpp
    src/main.cpp
    src/Options.cpp
)
target_link_libraries(bf PRIVATE termcolor::termcolor)

include(GNUInstallDirs)
install(TARGETS bf DESTINATION ${CMAKE_INSTALL_BINDIR})
