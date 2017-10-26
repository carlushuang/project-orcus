cmake_minimum_required(VERSION 3.2)
project(magnolia)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_POSITION_INDEPENDENT_CODE True)

file(GLOB magnolia_srcs
    src/*.cpp)

add_executable(magnolia ${magnolia_srcs})
