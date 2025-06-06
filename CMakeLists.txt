cmake_minimum_required(VERSION 3.13)

project(git-cpp)

set(CMAKE_CXX_STANDARD 23) # Enable the C++23 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_executable(git ${SOURCE_FILES})

find_package(OpenSSL REQUIRED)

target_link_libraries(git -lz OpenSSL::Crypto)
