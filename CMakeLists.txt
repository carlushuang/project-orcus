cmake_minimum_required(VERSION 3.2)
project(orcus)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_POSITION_INDEPENDENT_CODE True)

file(GLOB_RECURSE orcus_srcs
    src/*.cpp)


# Specify the list of directories to search for cmake modules.
set(CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
)

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIRS})
    link_libraries(${OPENGL_LIBRARIES})
endif()

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

find_package(GLFW 3.0.0 REQUIRED)
if (GLFW_FOUND)
    include_directories(${GLFW_INCLUDE_DIRS})
    link_libraries(${GLFW_LIBRARIES})
endif()

find_package(Threads REQUIRED)
if (THREADS_FOUND)
    link_libraries(Threads::Threads)
endif()

add_executable(orcus ${orcus_srcs})
