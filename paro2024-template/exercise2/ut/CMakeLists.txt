add_executable(ScrabbleTests
 scrabble-tests.cpp)

target_link_libraries (ScrabbleTests PUBLIC Scrabble gtest_main)

add_test(NAME Scrabble
    COMMAND ScrabbleTests --gtest_output=xml:${CMAKE_BINARY_DIR}/junit/exercise1.junit.xml)
