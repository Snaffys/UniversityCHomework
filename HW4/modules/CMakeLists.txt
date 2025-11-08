add_library(stack STATIC stack/stack.c stack/stack.h)
target_include_directories(stack PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/stack)

add_library(queue STATIC queue/queue.c queue/queue.h)
target_include_directories(queue PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/queue)

