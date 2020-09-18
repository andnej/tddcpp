set(This UnitTest)

set(Sources
  SoundexTest.cpp
)

add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
  gtest_main
  gtest
  pthread
  Soundex
)