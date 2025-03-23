add_library(DayOfYear SHARED
  src/day-of-year.cpp
)

target_include_directories (DayOfYear PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(ut)
