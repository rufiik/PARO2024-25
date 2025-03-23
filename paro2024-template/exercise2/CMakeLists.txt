add_library(Scrabble SHARED
  src/scrabble.cpp
)

target_include_directories (Scrabble PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(ut)
