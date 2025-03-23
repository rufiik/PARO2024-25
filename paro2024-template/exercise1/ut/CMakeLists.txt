add_executable(DayOfYearTests
  day-of-year-tests.cpp)

target_link_libraries (DayOfYearTests PUBLIC DayOfYear gtest_main)

add_test(NAME DayOfYear
    COMMAND DayOfYearTests --gtest_output=xml:${CMAKE_BINARY_DIR}/junit/exercise1.junit.xml)
