//
// Created by hannes on 18.02.18.
//

#include <gtest/gtest-message.h>         // for Message
#include <gtest/gtest-test-part.h>       // for TestPartResult, TestFactoryImpl
#include <opencv2/core/cvstd.hpp>        // for String
#include <opencv2/core/persistence.hpp>  // for FileStorage, operator<<, ope...
#include <vector>                        // for vector
// IWYU pragma: no_include <opencv2/core/cvstd.inl.hpp>

#include "game.h"                        // for Game
#include "gtest/gtest_pred_impl.h"       // for EXPECT_EQ, AssertionResult
#include "season.h"                      // for Season
#include "team.h"                        // for Team
#include "video.h"                       // for Video

class DefaultSeasonFixture : public ::testing::Test
{
  protected:
    Season unit_{};
};

TEST_F(DefaultSeasonFixture, DefaultConstructor)
{
    EXPECT_EQ("", unit_.GetName());
    EXPECT_EQ("", unit_.GetFilename());
    EXPECT_TRUE(unit_.GetGames().empty());
}

TEST_F(DefaultSeasonFixture, SetName)
{
    auto arbitrary_season_name = "Season 2017/2018";
    unit_.SetName(arbitrary_season_name);
    EXPECT_EQ(arbitrary_season_name, unit_.GetName());
}

TEST_F(DefaultSeasonFixture, SetFilename)
{
    auto arbitrary_filename = "season_-2017-2018.yaml";
    unit_.SetName(arbitrary_filename);
    EXPECT_EQ(arbitrary_filename, unit_.GetName());
}

class ExampleSeasonFixture : public ::testing::Test
{
  protected:
    Season unit_{"Season 2017/2018", "season_-2017-2018.yaml"};
};

TEST_F(ExampleSeasonFixture, Constructor)
{
    EXPECT_EQ("Season 2017/2018", unit_.GetName());
    EXPECT_EQ("season_-2017-2018.yaml", unit_.GetFilename());
    EXPECT_TRUE(unit_.GetGames().empty());
}

TEST_F(ExampleSeasonFixture, AddGame)
{
    EXPECT_EQ(0, unit_.GetGames().size());
    unit_.AddGame(Game{1, Team{"Los Krachos"}, Team{"Gänsejäger"}});
    EXPECT_EQ(1, unit_.GetGames().size());
}

class FullSeasonFixture : public ::testing::Test
{
  protected:
    Season unit_{"Season 2017/2018", "season-2017-2018.yaml"};

    void SetUp() override {
        unit_.AddGame(Game{1, Team{"Los Krachos"}, Team{"Gänsejäger"}});
        Video video {"View 1", "/home/hannes/Videos/2016-02-15_NixIsFix.mp4"};
//        unit_.GetGame(1).AddVideo(video);
//        unit_.GetGame(1).AddVideo(Video{"View 1", "/home/hannes/Videos/2016-02-15_NixIsFix.mp4"});
    }
};

TEST_F(FullSeasonFixture, WriteSeasonToFile)
{
    cv::FileStorage file_storage(unit_.GetFilename(), cv::FileStorage::WRITE);
    file_storage << "season" << unit_;
    file_storage.release();

    Season season_from_file;
    file_storage.open(unit_.GetFilename(), cv::FileStorage::READ);
    file_storage["season"] >> season_from_file;
    file_storage.release();

    EXPECT_EQ(unit_.GetName(), season_from_file.GetName());
    EXPECT_EQ(unit_.GetFilename(), season_from_file.GetFilename());
    EXPECT_EQ(unit_.GetGames(), season_from_file.GetGames());
}
