cmake_minimum_required(VERSION 3.2)
project(searchEngine)

set(CMAKE_CXX_STANDARD 17)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)

add_executable(searchEngine main.cpp
        include/ConverterJSON.h
        include/ProgrammExceptions.h
        include/InvertedIndex.h
        include/SearchServer.h
)

target_link_libraries(searchEngine PRIVATE nlohmann_json::nlohmann_json)
add_subdirectory(Tests)