cmake_minimum_required(VERSION 3.28)
project(SearchEngine2)

set(CMAKE_CXX_STANDARD 17)

set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(nlohmann_json)
add_executable(SearchEngine2 main.cpp
        include/ConverterJSON.h
        src/ConverterJSON.cpp
        include/InvertedIndex.h
        include/SearchEngine.h
        src/InvertedIndex.cpp
        src/SearchEngine.cpp
        include/CustomExceptions.h)

add_subdirectory(tests)
target_include_directories(SearchEngine2 PUBLIC include)
target_link_libraries(SearchEngine2 PRIVATE nlohmann_json::nlohmann_json)