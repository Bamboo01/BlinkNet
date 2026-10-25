cmake_minimum_required(VERSION 3.20)
project(Blinknet CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Grab every library source under Source/ so CLion stops nagging about files not in a target.
file(GLOB_RECURSE BLINKNET_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.h
)

add_library(Blinknet STATIC ${BLINKNET_SOURCES})
target_include_directories(Blinknet PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)

# MinGW ignores #pragma comment(lib, ...), so link Winsock explicitly.
if (WIN32)
    target_link_libraries(Blinknet PUBLIC ws2_32)
endif ()

# Tests
enable_testing()

add_executable(BlinknetTests Tests/main.cpp)
target_link_libraries(BlinknetTests PRIVATE Blinknet)
add_test(NAME BlinknetTests COMMAND BlinknetTests)
