cmake_minimum_required(VERSION 3.10)
project(test)

set(CMAKE_CXX_STANDARD 17)

# Setting the default Debug configuration
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

set(SOURCES
    src/PhysicsUnit/physics_unit.h
    src/PhysicsUnits/physics_units.h
    src/PhysicsUnits/physics_units.cpp
    src/Engine/engine.h
    src/Engine/engine.cpp
    src/TestStand/test_stand.h
    src/TestStand/test_stand.cpp
    src/JsonReader/json_reader.h
    src/JsonReader/json_reader.cpp
    src/main.cpp)

add_executable(solution ${SOURCES})

# Compilation settings for Debug and Release modes
target_compile_options(solution PRIVATE
    $<$<CONFIG:Debug>:-g -fsanitize=address -Wall -Wextra -Werror>
    $<$<CONFIG:Release>:-O3 -Wall>
)

# Indication to copy config.json to the build directory
configure_file(config.json ${CMAKE_CURRENT_BINARY_DIR}/config.json COPYONLY)