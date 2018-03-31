//
// Created by hannes on 12.02.18.
//

#include <gtest/gtest-message.h>         // for Message
#include <gtest/gtest-test-part.h>       // for TestPartResult
#include <opencv2/core/persistence.hpp>  // for FileStorage, operator<<, ope...

#include "../src/player.h"               // for Player, Position, Position::...
#include "../src/team.h"                 // for Team
#include "gtest/gtest_pred_impl.h"       // for Test, EXPECT_EQ, EqHelper

class DefaultTeamFixture : public ::testing::Test
{
protected:
    DefaultTeamFixture() {}

    Team unit{};
};

TEST_F(DefaultTeamFixture, DefaultConstructor)
{
    EXPECT_EQ("", unit.GetName());
}

TEST_F(DefaultTeamFixture, SetName)
{
    EXPECT_EQ("", unit.GetName());
    unit.SetName("Los Krachos");
    EXPECT_EQ("Los Krachos", unit.GetName());
}

TEST(Team, Constructor)
{
    Team unit{"Los Krachos"};
    EXPECT_EQ("Los Krachos", unit.GetName());
}

TEST(Team, FileInAndOutput)
{
    Team unit{"Los Krachos"};
    unit.AddPlayer(Player{"Hannes",9,Position::MITTELBLOCKER});
    unit.AddPlayer(Player{"Michi",6,Position::AUSSENANGREIFER});

    static const char *const filename = "/home/hannes/workspace/data.yaml";

    cv::FileStorage file_storage(filename, cv::FileStorage::WRITE);
    file_storage << "team" << unit;
    file_storage.release();

    Team teamFromFile;
    file_storage.open(filename,cv::FileStorage::READ);
    file_storage["team"] >> teamFromFile;
    file_storage.release();

    EXPECT_EQ(unit.GetName(), teamFromFile.GetName());
    EXPECT_EQ(unit.GetPlayers(), teamFromFile.GetPlayers());
}
