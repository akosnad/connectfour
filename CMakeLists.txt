cmake_minimum_required(VERSION 3.22)
project(connectfour)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

include_directories(libnadak)
include_directories(libnadak/itk_graphicslib)
add_subdirectory(libnadak nadak_lib)

add_compile_options("-Wall")

add_executable(connectfour main.cpp cell.cpp field.cpp)
target_link_libraries(connectfour nadak_lib)
