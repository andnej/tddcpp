#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../CommandLineInterface.hpp"

struct CommandLineInterfaceTest : public testing::Test
{
  void SetUp() override {
    cli = std::make_unique<CommandLineInterface>();
  }

  void TearDown() override {
    cli.reset();
  }
  std::unique_ptr<CommandLineInterface> cli;
};

TEST_F(CommandLineInterfaceTest, InitialCursorPosition) {
  EXPECT_THAT(cli->cursor(), ::testing::Eq(0));
  EXPECT_THAT(cli->capacity(), ::testing::Eq(CommandLineInterface::InitialCapacity));
  EXPECT_THAT(cli->toString(), ::testing::Eq(""));
}

TEST_F(CommandLineInterfaceTest, TypeOneChar) {
  cli->type('a');
  EXPECT_THAT(cli->cursor(), ::testing::Eq(1));
  EXPECT_THAT(cli->capacity(), ::testing::Eq(CommandLineInterface::InitialCapacity));
  EXPECT_THAT(cli->toString(), ::testing::Eq("a"));
}

TEST_F(CommandLineInterfaceTest, TypeThreeChar) {
  cli->type('a');
  cli->type('b');
  cli->type('c');
  EXPECT_THAT(cli->cursor(), ::testing::Eq(3));
  EXPECT_THAT(cli->capacity(), ::testing::Eq(CommandLineInterface::InitialCapacity));
  EXPECT_THAT(cli->toString(), ::testing::Eq("abc"));
}

TEST_F(CommandLineInterfaceTest, TypeFourChar) {
  cli->type('a');
  cli->type('b');
  cli->type('c');
  cli->type('d');
  EXPECT_THAT(cli->cursor(), ::testing::Eq(4));
  EXPECT_THAT(cli->capacity(), ::testing::Eq(2 * CommandLineInterface::InitialCapacity));
  EXPECT_THAT(cli->toString(), ::testing::Eq("abcd"));
}

TEST_F(CommandLineInterfaceTest, TypeFiveChar) {
  cli->type('a');
  cli->type('b');
  cli->type('c');
  cli->type('d');
  cli->type('e');
  EXPECT_THAT(cli->cursor(), ::testing::Eq(5));
  EXPECT_THAT(cli->capacity(), ::testing::Eq(2 * CommandLineInterface::InitialCapacity));
  EXPECT_THAT(cli->toString(), ::testing::Eq("abcde"));
}

TEST_F(CommandLineInterfaceTest, InitialMoveRight) {
  EXPECT_THAT(cli->right()->cursor(), ::testing::Eq(0));
}

TEST_F(CommandLineInterfaceTest, InitialMoveLeft) {
  EXPECT_THAT(cli->left()->cursor(), ::testing::Eq(0));
}

TEST_F(CommandLineInterfaceTest, TypeThenMoveLeft) {
  EXPECT_THAT(cli->type('c')->left()->cursor(), ::testing::Eq(0));
}

TEST_F(CommandLineInterfaceTest, TypeMoveLeftThenMoveRight) {
  EXPECT_THAT(cli->type('c')->left()->right()->cursor(), ::testing::Eq(1));
}

TEST_F(CommandLineInterfaceTest, TypeTwoCharMoveLeftThenType) {
  cli->type('1')->type('2')->left()->type('3');
  EXPECT_THAT(cli->cursor(), ::testing::Eq(2));
  EXPECT_THAT(cli->toString(), ::testing::Eq("132"));
}