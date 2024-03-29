cmake_minimum_required(VERSION 3.12)

project(spmcgame VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)

if(NOT CMAKE_CXX_EXTENSIONS)
  set(CMAKE_CXX_EXTENSION OFF)
endif()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_executable(spmcgame
  SourceFiles/Core/Window.cpp
  SourceFiles/Core/ButtonsCallback.hpp
  SourceFiles/Core/stb_image.hpp
  SourceFiles/Core/PngLoader.hpp
)

#add_subdirectory(./Includes/glfw)
find_package(glfw3 REQUIRED)
target_link_libraries(spmcgame glfw)

find_package(GLEW REQUIRED)
target_link_libraries(spmcgame GLEW::GLEW)

find_package(OpenGL REQUIRED)
target_link_libraries(spmcgame OpenGL::GL)


find_package(SDL2 REQUIRED)
target_link_libraries(spmcgame SDL2)

file(MAKE_DIRECTORY build/data)
file(COPY Assets DESTINATION data)
