cmake_minimum_required(VERSION 3.15)
project(test)

set(CMAKE_CXX_STANDARD 17)

# Checking the mandatory CMAKE_BUILD_TYPE
if(NOT CMAKE_BUILD_TYPE)
    message(FATAL_ERROR "Error: Please specify the build type with -DCMAKE_BUILD_TYPE=<Debug|Release>")
endif()

set(SOURCES
    ${PROJECT_SOURCE_DIR}/src/PhysicsUnit/physics_unit.h
    ${PROJECT_SOURCE_DIR}/src/PhysicsUnits/physics_units.h
    ${PROJECT_SOURCE_DIR}/src/PhysicsUnits/physics_units.cpp
    ${PROJECT_SOURCE_DIR}/src/Engine/engine.h
    ${PROJECT_SOURCE_DIR}/src/Engine/engine.cpp
    ${PROJECT_SOURCE_DIR}/src/TestStand/test_stand.h
    ${PROJECT_SOURCE_DIR}/src/TestStand/test_stand.cpp
    ${PROJECT_SOURCE_DIR}/src/JsonReader/json_reader.h
    ${PROJECT_SOURCE_DIR}/src/JsonReader/json_reader.cpp
    ${PROJECT_SOURCE_DIR}/src/CSV_Saver/csv_saver.h
    ${PROJECT_SOURCE_DIR}/src/CSV_Saver/csv_saver.cpp
    ${PROJECT_SOURCE_DIR}/src/json.hpp
    ${PROJECT_SOURCE_DIR}/src/main.cpp)

add_executable(solution ${SOURCES})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Добавляем флаги для Debug
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fsanitize=address -Wall -Wextra -Werror")
    set(CMAKE_CXX_LINKER_FLAGS "${CMAKE_CXX_LINKER_FLAGS} -fsanitize=address")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    # Добавляем флаги для Release
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall")
    set(CMAKE_CXX_LINKER_FLAGS "${CMAKE_CXX_LINKER_FLAGS}")
endif()

# Indication to copy config.json to the build directory
configure_file(config.json ${CMAKE_CURRENT_BINARY_DIR}/config.json COPYONLY)