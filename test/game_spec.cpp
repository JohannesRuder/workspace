//
// Created by hannes on 17.02.18.
//

#include <gtest/gtest-message.h>         // for Message
#include <gtest/gtest-test-part.h>       // for TestPartResult, TestFactoryImpl
#include <opencv2/core/persistence.hpp>  // for FileStorage, operator<<, ope...
#include <vector>                        // for vector

#include "game.h"                        // for Game
#include "gtest/gtest_pred_impl.h"       // for AssertionResult, EXPECT_EQ
#include "team.h"                        // for Team
#include "video.h"                       // for Video
// IWYU pragma: no_include <opencv2/core/cvstd.inl.hpp>

class DefaultGameFixture : public ::testing::Test
{
  protected:
    DefaultGameFixture() {}

    Game unit_{};
};

TEST_F(DefaultGameFixture, DefaultConstructor)
{
    EXPECT_EQ(0, unit_.GetNumber());
    EXPECT_EQ(Team{}, unit_.GetHomeTeam());
    EXPECT_EQ(Team{}, unit_.GetGuestTeam());
    EXPECT_TRUE(unit_.GetSets().empty());
    EXPECT_TRUE(unit_.GetVideos().empty());
    EXPECT_TRUE(unit_.GetVideoFrames().empty());
}

TEST_F(DefaultGameFixture, SetNumber)
{
    int arbitrary_number{5};
    unit_.SetNumber(arbitrary_number);
    EXPECT_EQ(arbitrary_number, unit_.GetNumber());
}

TEST_F(DefaultGameFixture, SetHomeTeam)
{
    Team arbitrary_team{"Los Krachos"};
    unit_.SetHomeTeam(arbitrary_team);
    EXPECT_EQ(arbitrary_team, unit_.GetHomeTeam());
}

TEST_F(DefaultGameFixture, SetGuestTeam)
{
    Team arbitrary_team{"Los Krachos"};
    unit_.SetGuestTeam(arbitrary_team);
    EXPECT_EQ(arbitrary_team, unit_.GetGuestTeam());
}

TEST_F(DefaultGameFixture, AddVideo)
{
    EXPECT_EQ(0, unit_.GetVideos().size());
    unit_.AddVideo(Video{"View 1", "/home/hannes/Videos/2016-02-15_NixIsFix.mp4"});
    EXPECT_EQ(1, unit_.GetVideos().size());
}

class ExampleGameFixture : public ::testing::Test
{
  protected:
    Game unit_{1, Team{"Los Krachos"}, Team{"Nix is fix"}};

    virtual void SetUp() { unit_.AddVideo(Video{"View 1", "/home/hannes/Videos/2016-02-15_NixIsFix.mp4"}); }
};

TEST_F(ExampleGameFixture, WriteGameToFile)
{
    static const char* const filename = "/home/hannes/workspace/data.yaml";

    cv::FileStorage file_storage(filename, cv::FileStorage::WRITE);
    file_storage << "game" << unit_;
    file_storage.release();

    Game game_from_file;
    file_storage.open(filename, cv::FileStorage::READ);
    file_storage["game"] >> game_from_file;
    file_storage.release();

    EXPECT_EQ(unit_, game_from_file);
}
