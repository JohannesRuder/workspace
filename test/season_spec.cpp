//
// Created by hannes on 18.02.18.
//

#include "../src/season.h"
#include <gtest/gtest.h>

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
    QString arbitrary_season_name = "Season 2017/2018";
    unit_.SetName(arbitrary_season_name);
    EXPECT_EQ(arbitrary_season_name, unit_.GetName());
}

TEST_F(DefaultSeasonFixture, SetFilename)
{
    QString arbitrary_filename = "season_-2017-2018.yaml";
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

TEST_F(ExampleSeasonFixture, WriteSeasonToFile)
{
    static const char *const filename = "/home/hannes/workspace/data.yaml";

    cv::FileStorage file_storage(filename, cv::FileStorage::WRITE);
    file_storage << "season_" << unit_;
    file_storage.release();

    Season season_from_file;
    file_storage.open(filename,cv::FileStorage::READ);
    file_storage["season_"] >> season_from_file;
    file_storage.release();

    EXPECT_EQ(unit_.GetName(), season_from_file.GetName());
    EXPECT_EQ(unit_.GetFilename(), season_from_file.GetFilename());
    EXPECT_EQ(unit_.GetGames(), season_from_file.GetGames());
}
