cmake_minimum_required(VERSION 3.16)
project(inventory_management_system LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(inventory_core
    src/inventory.cpp
)

target_include_directories(inventory_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(inventory_core PRIVATE -Wall -Wextra -Wpedantic)

add_executable(inventory_app
    src/main.cpp
)

target_link_libraries(inventory_app PRIVATE inventory_core)

add_executable(inventory_tests
    tests/test_inventory.cpp
)

target_link_libraries(inventory_tests PRIVATE inventory_core)

enable_testing()
add_test(NAME inventory_tests COMMAND inventory_tests)
