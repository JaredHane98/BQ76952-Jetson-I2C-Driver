cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(BQ76952_DRIVER)



add_compile_options(-fPIC)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()



add_executable(${PROJECT_NAME}
                main.cpp)


include_directories(${PROJECT_SOURCE_DIR})
