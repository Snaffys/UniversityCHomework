add_executable(parenthesesBalance src/main.c)

target_link_libraries(parenthesesBalance stack)
target_include_directories(parenthesesBalance PRIVATE ${CMAKE_SOURCE_DIR}/modules)

