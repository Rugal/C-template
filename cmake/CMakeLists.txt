#C
cmake_minimum_required(VERSION 3.20.0)
PROJECT(Rugal C)
SET(CMAKE_C_FLAGS "-O0 -ggdb -Wall -std=c17")
SET(CMAKE_C_COMPILER gcc)
SET(BIN "a.out")

SET(SOURCE
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/implement/person.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/implement/chopstick.c
)

ADD_EXECUTABLE(${BIN} ${SOURCE})

TARGET_INCLUDE_DIRECTORIES(${BIN} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/include)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${BIN} PRIVATE Threads::Threads)

add_custom_target(test ${BIN} ./${BIN})
