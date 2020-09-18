#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../Soundex.hpp"

class SoundexEncoding : public testing::Test
{
private:
  /* data */
public:
  Soundex soundex;
};

TEST_F(SoundexEncoding, RetainSoleLetterOneWord) {
  auto encoded = soundex.encode("A");

  ASSERT_THAT(encoded, ::testing::Eq("A000"));
}

TEST_F(SoundexEncoding, EnsureZeroPads) {
  auto encoded = soundex.encode("I");

  ASSERT_THAT(encoded, ::testing::Eq("I000"));
}

TEST_F(SoundexEncoding, TurnConsonantIntoDigit) {
  auto encoded = soundex.encode("Ab");

  ASSERT_THAT(encoded, ::testing::Eq("A100"));

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);;
  return RUN_ALL_TESTS();
}