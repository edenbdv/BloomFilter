cmake_minimum_required(VERSION 3.14)
project("BloomFilter") 

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
googletest
URL
https://github.com/google/googletest/archive/03597a01ee50ed
33e9dfd640b249b4be3799d395.zip
)

enable_testing()

set(SOURCE_FILES
src/App.cpp
src/Menu.cpp 
src/BloomFilter.cpp 
src/IHash.h
src/Hashs/StdHash.cpp
src/Hashs/DoubleStdHash.cpp
src/Commands/AddUrlCommand.cpp
src/Commands/ContainsUrlCommand.cpp
tests/TestHelpers.cpp
)

set(TEST_FILES
tests/test_main.cpp # this is the main for tests
tests/MenuTest.cpp 
tests/BloomFilterTest.cpp 
tests/HashsTest.cpp
tests/InputTest.cpp
)

add_executable(BloomFilterTests ${TEST_FILES} )


target_sources(BloomFilterTests PRIVATE
    ${TEST_FILES}
    ${SOURCE_FILES} 
)

# Include the source directory for tests
target_include_directories(BloomFilterTests PRIVATE src)

# Link Google Test to the test executable
target_link_libraries(BloomFilterTests PRIVATE gtest gtest_main pthread)

include(GoogleTest)
gtest_discover_tests(BloomFilterTests)