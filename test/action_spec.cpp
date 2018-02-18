//
// Created by hannes on 16.02.18.
//

#include "../src/action.h"
#include <gtest/gtest.h>


class DefaultActionFixture : public ::testing::Test
{
  protected:
    Action unit{};
};

TEST_F(DefaultActionFixture, DefaultConstructor)
{
    EXPECT_TRUE(unit.GetTime().isNull());
}

TEST_F(DefaultActionFixture, SetTime)
{
    const QTime& arbitrary_time{9, 37, 20, 333};
    unit.SetTime(arbitrary_time);
    EXPECT_EQ(arbitrary_time, unit.GetTime());
}

class ExampleActionFixture : public ::testing::Test
{
  protected:
    const QTime arbitrary_time{9, 37, 20, 333};
    Action unit{arbitrary_time};
};

TEST_F(ExampleActionFixture, Constructor)
{
    EXPECT_EQ(arbitrary_time, unit.GetTime());
}

TEST_F(ExampleActionFixture, WriteActionToFile)
{
    static const char* const filename = "/home/hannes/workspace/data.yaml";

    cv::FileStorage file_storage(filename, cv::FileStorage::WRITE);
    file_storage << "action" << unit;
    file_storage.release();

    Action actionFromFile;
    file_storage.open(filename, cv::FileStorage::READ);
    file_storage["action"] >> actionFromFile;
    file_storage.release();

    EXPECT_EQ(unit.GetTime(), actionFromFile.GetTime());
}
