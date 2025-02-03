cmake_minimum_required(VERSION 3.28)
project(tests)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(tests
        ${SrcFiles}
        ${IncludeFiles}

        InvertedIndex_test.cpp
        SearchEngine_test.cpp
)

target_sources(tests PRIVATE ../src/InvertedIndex.cpp
        ../src/SearchEngine.cpp
        ../src/ConverterJSON.cpp)

target_link_libraries(tests PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(tests PUBLIC ${INCLUDE})
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_link_libraries(tests PRIVATE gtest gtest_main)


include(GoogleTest)
gtest_discover_tests(tests)
