#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../Soundex.hpp"

TEST(SoundexEncoding, RetainSoleLetterOneWord) {
  Soundex soundex;
  auto encoded = soundex.encode("A");

  ASSERT_THAT(encoded, ::testing::Eq("A"));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);;
  return RUN_ALL_TESTS();
}