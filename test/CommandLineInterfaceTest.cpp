#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../CommandLineInterface.hpp"

struct CharBasedCommandLineInterfaceTest : public testing::Test
{
  void SetUp() override {
    cli = std::make_unique<CharBasedCommandLineInterface>();
  }

  void TearDown() override {
    cli.reset();
  }
  std::unique_ptr<CharBasedCommandLineInterface> cli;
};

TEST_F(CharBasedCommandLineInterfaceTest, InitialCursorPosition) {
  EXPECT_THAT(cli->cursor(), ::testing::Eq(0));
  EXPECT_THAT(cli->capacity(), ::testing::Eq(CommandLineInterface::InitialCapacity));
  EXPECT_THAT(cli->toString(), ::testing::Eq(""));
}

TEST_F(CharBasedCommandLineInterfaceTest, TypeOneChar) {
  cli->type('a');
  EXPECT_THAT(cli->cursor(), ::testing::Eq(1));
  EXPECT_THAT(cli->capacity(), ::testing::Eq(CommandLineInterface::InitialCapacity));
  EXPECT_THAT(cli->toString(), ::testing::Eq("a"));
}

TEST_F(CharBasedCommandLineInterfaceTest, TypeThreeChar) {
  cli->type('a');
  cli->type('b');
  cli->type('c');
  EXPECT_THAT(cli->cursor(), ::testing::Eq(3));
  EXPECT_THAT(cli->capacity(), ::testing::Eq(CommandLineInterface::InitialCapacity));
  EXPECT_THAT(cli->toString(), ::testing::Eq("abc"));
}

TEST_F(CharBasedCommandLineInterfaceTest, TypeFourChar) {
  cli->type('a');
  cli->type('b');
  cli->type('c');
  cli->type('d');
  EXPECT_THAT(cli->cursor(), ::testing::Eq(4));
  EXPECT_THAT(cli->capacity(), ::testing::Eq(2 * CommandLineInterface::InitialCapacity));
  EXPECT_THAT(cli->toString(), ::testing::Eq("abcd"));
}

TEST_F(CharBasedCommandLineInterfaceTest, TypeFiveChar) {
  cli->type('a');
  cli->type('b');
  cli->type('c');
  cli->type('d');
  cli->type('e');
  EXPECT_THAT(cli->cursor(), ::testing::Eq(5));
  EXPECT_THAT(cli->capacity(), ::testing::Eq(2 * CommandLineInterface::InitialCapacity));
  EXPECT_THAT(cli->toString(), ::testing::Eq("abcde"));
}

TEST_F(CharBasedCommandLineInterfaceTest, InitialMoveRight) {
  EXPECT_THAT(cli->right()->cursor(), ::testing::Eq(0));
}

TEST_F(CharBasedCommandLineInterfaceTest, InitialMoveLeft) {
  EXPECT_THAT(cli->left()->cursor(), ::testing::Eq(0));
}

TEST_F(CharBasedCommandLineInterfaceTest, TypeThenMoveLeft) {
  EXPECT_THAT(cli->type('c')->left()->cursor(), ::testing::Eq(0));
}

TEST_F(CharBasedCommandLineInterfaceTest, TypeMoveLeftThenMoveRight) {
  EXPECT_THAT(cli->type('c')->left()->right()->cursor(), ::testing::Eq(1));
}

TEST_F(CharBasedCommandLineInterfaceTest, TypeTwoCharMoveLeftThenType) {
  cli->type('1')->type('2')->left()->type('3');
  EXPECT_THAT(cli->cursor(), ::testing::Eq(2));
  EXPECT_THAT(cli->toString(), ::testing::Eq("132"));
}

TEST_F(CharBasedCommandLineInterfaceTest, CopyConstructor) {
  cli->type('a')->type('b')->type('c')->type('d')->type('e')->left()->left();
  auto otherCli = CharBasedCommandLineInterface(*cli.get());
  EXPECT_THAT(otherCli.toString(), ::testing::Eq(cli->toString()));
  EXPECT_THAT(otherCli.capacity(), ::testing::Eq(cli->capacity()));
  EXPECT_THAT(otherCli.cursor(), ::testing::Eq(cli->cursor()));
}

TEST_F(CharBasedCommandLineInterfaceTest, EqualOperator) {
  cli->type('a')->type('b')->type('c')->type('d')->type('e')->left()->left();
  CharBasedCommandLineInterface othercli = *cli.get();
  CharBasedCommandLineInterface copied = othercli;
  EXPECT_THAT(copied.toString(), ::testing::Eq(cli->toString()));
  EXPECT_THAT(copied.capacity(), ::testing::Eq(cli->capacity()));
  EXPECT_THAT(copied.cursor(), ::testing::Eq(cli->cursor()));
}