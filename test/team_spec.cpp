//
// Created by hannes on 12.02.18.
//

#include "../src/team.h"
#include "gtest/gtest.h"

class DefaultTeamFixture : public ::testing::Test
{
  protected:
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
