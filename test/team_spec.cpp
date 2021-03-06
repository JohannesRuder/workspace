//
// Created by hannes on 12.02.18.
//

#include <gtest/gtest-message.h>         // for Message
#include <gtest/gtest-test-part.h>       // for TestPartResult, TestFactoryImpl
#include <opencv2/core/persistence.hpp>  // for FileStorage, operator<<, ope...
// IWYU pragma: no_include <opencv2/core/cvstd.inl.hpp>

#include "player.h"          // for Player, Position, Position::...
#include "team.h"            // for Team
#include "gtest/gtest_pred_impl.h"  // for Test, EXPECT_EQ, EqHelper, TEST

class DefaultTeamFixture : public ::testing::Test
{
  protected:
    DefaultTeamFixture() = default;

    Team unit_{};
};

TEST_F(DefaultTeamFixture, DefaultConstructor)
{
    EXPECT_EQ("", unit_.GetName());
}

TEST_F(DefaultTeamFixture, SetName)
{
    EXPECT_EQ("", unit_.GetName());
    unit_.SetName("Los Krachos");
    EXPECT_EQ("Los Krachos", unit_.GetName());
}

TEST(Team, Constructor)
{
    Team unit{"Los Krachos"};
    EXPECT_EQ("Los Krachos", unit.GetName());
}

TEST(Team, FileInAndOutput)
{
    Team unit{"Los Krachos"};
    unit.AddPlayer(Player{"Hannes", 9, Position::kMITTELBLOCKER});
    unit.AddPlayer(Player{"Michi", 6, Position::kAUSSENANGREIFER});

    static const char* const filename = "/home/hannes/workspace/data.yaml";

    cv::FileStorage file_storage(filename, cv::FileStorage::WRITE);
    file_storage << "team" << unit;
    file_storage.release();

    Team team_from_file;
    file_storage.open(filename, cv::FileStorage::READ);
    file_storage["team"] >> team_from_file;
    file_storage.release();

    EXPECT_EQ(unit.GetName(), team_from_file.GetName());
    EXPECT_EQ(unit.GetPlayers(), team_from_file.GetPlayers());
}
