cmake_minimum_required(VERSION 3.14)
project(Greenhouse)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

cmake_policy(SET CMP0135 NEW)

set(CMAKE_CXX_STANDARD 17)
include_directories(includes)

add_executable(app src/main.cpp src/database.cpp src/sqlite3.c)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(unit_tests tests/test_logic.cpp src/database.cpp src/sqlite3.c)
target_link_libraries(unit_tests gtest_main)
add_test(NAME GreenhouseTests COMMAND unit_tests)

