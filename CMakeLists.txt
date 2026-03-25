cmake_minimum_required(VERSION 3.10)
project(UniversityCHomework)

set(HW_FOLDERS Term2-HW5-States)

add_custom_target(lint)

foreach(HW ${HW_FOLDERS})
    add_custom_command(TARGET lint
        COMMAND ${CMAKE_COMMAND} -E echo "Running lint in ${HW}"
        COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_SOURCE_DIR}/${HW} make format-check
        COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_SOURCE_DIR}/${HW} make tidy
    )
endforeach()

add_custom_target(test)

foreach(HW ${HW_FOLDERS})
    add_custom_command(TARGET test
        COMMAND ${CMAKE_COMMAND} -E echo "Running tests in ${HW}"
        COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_SOURCE_DIR}/${HW} make test
    )
endforeach()
