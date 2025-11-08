cmake_minimum_required(VERSION 3.25)
project(homework4 C)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    message(STATUS "Using GCC/Clang warnings")
    add_compile_options(-Wall -Wextra -Wpedantic)
elseif(MSVC)
    message(STATUS "Using MSVC warnings")  
    add_compile_options(/W4)
else()
    message(STATUS "Unknown compiler - using default warnings")
endif()

add_subdirectory(modules)
add_subdirectory(ParenthesesBalance)
add_subdirectory(ShuntingYard)

