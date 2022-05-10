cmake_minimum_required(VERSION 3.22)
project(connectfour)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

include_directories(libnadak)
include_directories(libnadak/itk_graphicslib)
add_subdirectory(libnadak nadak_lib)

add_compile_options("-Wall")

add_executable(connectfour main.cpp cell.cpp field.cpp game.cpp)
target_link_libraries(connectfour nadak_lib)

ADD_CUSTOM_TARGET(assets ALL  COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets )
