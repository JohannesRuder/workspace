//
// Created by hannes on 12.02.18.
//

#include <gtest/gtest-message.h>         // for Message
#include <gtest/gtest-test-part.h>       // for TestPartResult
#include <opencv2/core/persistence.hpp>  // for FileStorage, operator<<, ope...

#include "../src/player.h"               // for Player, Position, Position::...
#include "gtest/gtest_pred_impl.h"       // for AssertionResult, EXPECT_EQ

class DefaultPlayerFixture : public ::testing::Test
{
protected:
    Player unit_{};
};

TEST_F(DefaultPlayerFixture, DefaultConstructor)
{
    EXPECT_EQ("", unit_.GetName());
    EXPECT_EQ(0, unit_.GetNumber());
    EXPECT_EQ(Position::UNDEFINED, unit_.GetPosition());
    EXPECT_EQ(0, unit_.GetNumberOfActions());
}

TEST_F(DefaultPlayerFixture, IncrementNumberOfActions)
{
    EXPECT_EQ(0, unit_.GetNumberOfActions());

    unit_.IncrementNumberOfActions();

    EXPECT_EQ(1, unit_.GetNumberOfActions());
}

class ExamplePlayerFixture : public ::testing::Test
{
protected:
    Player unit_{"Hannes", 9, Position::MITTELBLOCKER};
};

TEST_F(ExamplePlayerFixture, Constructor)
{
    EXPECT_EQ("Hannes", unit_.GetName());
    EXPECT_EQ(9, unit_.GetNumber());
    EXPECT_EQ(Position::MITTELBLOCKER, unit_.GetPosition());
    EXPECT_EQ(0, unit_.GetNumberOfActions());
}

TEST_F(ExamplePlayerFixture, WritePlayerToFile)
{
    static const char *const filename = "/home/hannes/workspace/data.yaml";

    cv::FileStorage file_storage(filename, cv::FileStorage::WRITE);
    file_storage << "player" << unit_;
    file_storage.release();

    Player player_from_file;
    file_storage.open(filename,cv::FileStorage::READ);
    file_storage["player"] >> player_from_file;
    file_storage.release();

    EXPECT_EQ(unit_.GetName(), player_from_file.GetName());
    EXPECT_EQ(unit_.GetNumber(), player_from_file.GetNumber());
    EXPECT_EQ(unit_.GetPosition(), player_from_file.GetPosition());
    EXPECT_EQ(unit_.GetNumberOfActions(), player_from_file.GetNumberOfActions());
}

TEST_F(ExamplePlayerFixture, ComparePlayers_AllEqual)
{
    Player player{"Hannes",9,Position::MITTELBLOCKER};
    EXPECT_TRUE(unit_ == player);
}

TEST_F(ExamplePlayerFixture, ComparePlayers_DifferentName)
{
    Player player{"Michi",9,Position::MITTELBLOCKER};
    EXPECT_FALSE(unit_ == player);
}

TEST_F(ExamplePlayerFixture, ComparePlayers_DifferentNumber)
{
    Player player{"Hannes",6,Position::MITTELBLOCKER};
    EXPECT_FALSE(unit_ == player);
}

TEST_F(ExamplePlayerFixture, ComparePlayers_DifferentPosition1)
{
    Player player{"Hannes",9,Position::AUSSENANGREIFER};
    EXPECT_TRUE(unit_ == player);
}
