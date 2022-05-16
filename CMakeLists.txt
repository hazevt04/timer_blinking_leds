cmake_minimum_required(VERSION 3.5)

project(timer_blinking_leds LANGUAGES C)

include_directories( "${CMAKE_SOURCE_DIR}" )

set(EXEC_NAME "${CMAKE_PROJECT_NAME}")

set(SRCS
   "main.c"
   )

add_executable("${EXEC_NAME}" "${SRCS}")

target_link_libraries("${EXEC_NAME}" gpiod)

install(TARGETS "${EXEC_NAME}" DESTINATION "${CMAKE_SOURCE_DIR}/bin")
