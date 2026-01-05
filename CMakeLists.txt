cmake_minimum_required(VERSION 3.16)

project(traceroute
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()


add_executable(traceroute
    main.cpp
    icmp/Icmp.cpp
)


target_include_directories(traceroute PRIVATE
    ${PROJECT_SOURCE_DIR}/icmp
)


if (APPLE)
    target_link_libraries(traceroute PRIVATE)
endif()
