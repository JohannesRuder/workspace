//
// Created by hannes on 18.02.18.
//

#include <gtest/gtest-message.h>         // for Message
#include <gtest/gtest-test-part.h>       // for TestPartResult
#include <opencv2/core/cvstd.hpp>        // for String
#include <opencv2/core/persistence.hpp>  // for FileStorage, operator<<, ope...
#include <vector>                        // for vector

#include "../src/game.h"                 // for Game
#include "../src/season.h"               // for Season
#include "gtest/gtest_pred_impl.h"       // for EXPECT_EQ, AssertionResult

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
    Season unit_{"Season 2017/2018","season_-2017-2018.yaml"};
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
    unit_.AddGame(Game{});
    EXPECT_EQ(1, unit_.GetGames().size());
}

TEST_F(ExampleSeasonFixture, WriteSeasonToFile)
{
    unit_.AddGame(Game{});

    cv::FileStorage file_storage(unit_.GetFilename(), cv::FileStorage::WRITE);
    file_storage << "season_" << unit_;
    file_storage.release();

    Season season_from_file;
    file_storage.open(unit_.GetFilename(),cv::FileStorage::READ);
    file_storage["season_"] >> season_from_file;
    file_storage.release();

    EXPECT_EQ(unit_.GetName(), season_from_file.GetName());
    EXPECT_EQ(unit_.GetFilename(), season_from_file.GetFilename());
    EXPECT_EQ(unit_.GetGames(), season_from_file.GetGames());
}
