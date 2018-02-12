//
// Created by hannes on 12.02.18.
//

#include "../src/player.h"
#include "gtest/gtest.h"

class DefaultPlayerFixture : public ::testing::Test
{
  protected:
    Player unit{};
};

TEST_F(DefaultPlayerFixture, DefaultConstructor)
{
    EXPECT_EQ("", unit.GetName());
    EXPECT_EQ(0, unit.GetNumber());
    EXPECT_EQ(Position::UNDEFINED, unit.GetPosition());
    EXPECT_EQ(0, unit.GetNumberOfActions());
}

TEST_F(DefaultPlayerFixture, IncrementNumberOfActions)
{
    EXPECT_EQ(0, unit.GetNumberOfActions());

    unit.IncrementNumberOfActions();

    EXPECT_EQ(1, unit.GetNumberOfActions());
}

class ExamplePlayerFixture : public ::testing::Test
{
  protected:
    Player unit{"Hannes", 9, Position::MITTELBLOCKER};
};

TEST_F(ExamplePlayerFixture, Constructor)
{
    EXPECT_EQ("Hannes", unit.GetName());
    EXPECT_EQ(9, unit.GetNumber());
    EXPECT_EQ(Position::MITTELBLOCKER, unit.GetPosition());
    EXPECT_EQ(0, unit.GetNumberOfActions());
}

TEST_F(ExamplePlayerFixture, WritePlayerToFile)
{
    static const char *const filename = "/home/hannes/workspace/data.yaml";

    cv::FileStorage file_storage(filename, cv::FileStorage::WRITE);
    file_storage << "player" << unit;
    file_storage.release();

    Player playerFromFile;
    file_storage.open(filename,cv::FileStorage::READ);
    file_storage["player"] >> playerFromFile;
    file_storage.release();

    EXPECT_EQ(unit.GetName(), playerFromFile.GetName());
    EXPECT_EQ(unit.GetNumber(), playerFromFile.GetNumber());
    EXPECT_EQ(unit.GetNumberOfActions(), playerFromFile.GetNumberOfActions());
}
