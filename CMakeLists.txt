

cmake_minimum_required(VERSION 3.16)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set the project name
project(BrownianMotion VERSION 0.1.0)

# add the executable
file(GLOB_RECURSE SOURCES1 "src/*.cpp")

add_executable(BrownianMotion ${SOURCES1})

# Set standard version
set_property(TARGET BrownianMotion PROPERTY CXX_STANDARD 20)
set_property(TARGET BrownianMotion PROPERTY C_STANDARD 17)

# Add include dirs
target_include_directories(BrownianMotion PRIVATE "src")
target_include_directories(BrownianMotion PRIVATE "${PROJECT_BINARY_DIR}")

# Set warning options
if(MSVC)
  target_compile_options(BrownianMotion PRIVATE /W4 /WX)
else()
  target_compile_options(BrownianMotion PRIVATE -Wall -Wextra -Wpedantic -pedantic -fdiagnostics-color=always)
endif()

configure_file(src/config.h.in config.h)
