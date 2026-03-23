cmake_minimum_required(VERSION 3.10)
project(UniversityCHomework)

set(HW_FOLDERS Term2-HW4-AVLTree)

add_custom_target(lint)

foreach(HW ${HW_FOLDERS})
    add_custom_command(TARGET lint
        COMMAND ${CMAKE_COMMAND} -E echo "Running lint in ${HW}"
        COMMAND make -C ${HW} format-check
        COMMAND make -C ${HW} tidy
    )
endforeach()

add_custom_target(test)

foreach(HW ${HW_FOLDERS})
    add_custom_command(TARGET test
        COMMAND ${CMAKE_COMMAND} -E echo "Running tests in ${HW}"
        COMMAND make -C ${HW} test
    )
endforeach()
