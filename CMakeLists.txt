cmake_minimum_required(VERSION 3.10)
project(PSU_myftp_2017 C)

set(CMAKE_C_STANDARD 99)

SET(GCC_COVERAGE_COMPILE_FLAGS    "-W -Wall -Werror -Wextra")

file(GLOB SOURCES
        "src/*.c"
        "src/init/*.c"
        "src/server/*.c"
        "src/command/*.c"
        "src/basics/*.c"
        )

file(GLOB INCLUDES
        "include/*.h"
        )


include_directories(include/)

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

add_executable(PSU_myftp_2017 ${SOURCES} ${INCLUDES})