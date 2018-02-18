//
// Created by hannes on 18.02.18.
//

#include "../src/season.h"
#include <gtest/gtest.h>

class DefaultSeasonFixture : public ::testing::Test
{
protected:
    Season unit{};
};

TEST_F(DefaultSeasonFixture, DefaultConstructor)
{
    EXPECT_EQ("", unit.GetName());
    EXPECT_EQ("", unit.GetFilename());
    EXPECT_TRUE(unit.GetGames().empty());
}

TEST_F(DefaultSeasonFixture, SetName)
{
    QString arbitrary_season_name = "Season 2017/2018";
    unit.SetName(arbitrary_season_name);
    EXPECT_EQ(arbitrary_season_name, unit.GetName());
}

TEST_F(DefaultSeasonFixture, SetFilename)
{
    QString arbitrary_filename = "season-2017-2018.yaml";
    unit.SetName(arbitrary_filename);
    EXPECT_EQ(arbitrary_filename, unit.GetName());
}

class ExampleSeasonFixture : public ::testing::Test
{
protected:
    Season unit{"Season 2017/2018","season-2017-2018.yaml"};
};

TEST_F(ExampleSeasonFixture, Constructor)
{
    EXPECT_EQ("Season 2017/2018", unit.GetName());
    EXPECT_EQ("season-2017-2018.yaml", unit.GetFilename());
    EXPECT_TRUE(unit.GetGames().empty());
}

TEST_F(ExampleSeasonFixture, WriteSeasonToFile)
{
    static const char *const filename = "/home/hannes/workspace/data.yaml";

    cv::FileStorage file_storage(filename, cv::FileStorage::WRITE);
    file_storage << "season" << unit;
    file_storage.release();

    Season season_from_file;
    file_storage.open(filename,cv::FileStorage::READ);
    file_storage["season"] >> season_from_file;
    file_storage.release();

    EXPECT_EQ(unit.GetName(), season_from_file.GetName());
    EXPECT_EQ(unit.GetFilename(), season_from_file.GetFilename());
    EXPECT_EQ(unit.GetGames(), season_from_file.GetGames());
}
