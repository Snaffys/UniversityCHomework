add_executable(shuntingYard src/main.c)

target_link_libraries(shuntingYard stack queue)
target_include_directories(shuntingYard PRIVATE ${CMAKE_SOURCE_DIR}/modules)

