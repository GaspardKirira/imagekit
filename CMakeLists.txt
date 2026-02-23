cmake_minimum_required(VERSION 3.20)
project(imagekit LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(imagekit INTERFACE)
add_library(imagekit::imagekit ALIAS imagekit)

target_include_directories(imagekit INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

if (MSVC)
  target_compile_options(imagekit INTERFACE /W4 /permissive-)
else()
  target_compile_options(imagekit INTERFACE -Wall -Wextra -Wpedantic)
endif()

include(CTest)
enable_testing()

add_executable(imagekit_basic_test tests/test_basic.cpp)
target_link_libraries(imagekit_basic_test PRIVATE imagekit::imagekit)
add_test(NAME imagekit.basic COMMAND imagekit_basic_test)
