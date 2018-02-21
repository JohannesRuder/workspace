//
// Created by hannes on 17.02.18.
//

#include "../src/game.h"
#include <gtest/gtest.h>

class DefaultGameFixture : public ::testing::Test
{
protected:
    Game unit{};
};

TEST_F(DefaultGameFixture, DefaultConstructor)
{
    EXPECT_EQ(0, unit.GetNumber());
    EXPECT_EQ(Team{}, unit.GetHomeTeam());
    EXPECT_EQ(Team{}, unit.GetGuestTeam());
    EXPECT_TRUE(unit.GetSets().empty());
    EXPECT_TRUE(unit.GetVideos().empty());
    EXPECT_TRUE(unit.GetVideoFrames().empty());
}

TEST_F(DefaultGameFixture, SetNumber)
{
    int arbitrary_number{5};
    unit.SetNumber(arbitrary_number);
    EXPECT_EQ(arbitrary_number, unit.GetNumber());
}

TEST_F(DefaultGameFixture, SetHomeTeam)
{
    Team arbitrary_team{"Los Krachos"};
    unit.SetHomeTeam(arbitrary_team);
    EXPECT_EQ(arbitrary_team, unit.GetHomeTeam());
}

TEST_F(DefaultGameFixture, SetGuestTeam)
{
    Team arbitrary_team{"Los Krachos"};
    unit.SetGuestTeam(arbitrary_team);
    EXPECT_EQ(arbitrary_team, unit.GetGuestTeam());
}

TEST_F(DefaultGameFixture, WritePlayerToFile)
{
    static const char *const filename = "/home/hannes/workspace/data.yaml";

    cv::FileStorage file_storage(filename, cv::FileStorage::WRITE);
    file_storage << "game" << unit;
    file_storage.release();

    Game game_from_file;
    file_storage.open(filename,cv::FileStorage::READ);
    file_storage["game"] >> game_from_file;
    file_storage.release();

    EXPECT_EQ(unit, game_from_file);
}