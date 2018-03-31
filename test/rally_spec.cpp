//
// Created by hannes on 16.02.18.
//

#include <gtest/gtest-message.h>         // for Message
#include <gtest/gtest-test-part.h>       // for TestPartResult
#include <opencv2/core/persistence.hpp>  // for FileStorage, operator<<, ope...
#include <qdatetime.h>                   // for QTime
#include <vector>                        // for vector

#include "../src/rally.h"                // for Rally
#include "gtest/gtest_pred_impl.h"       // for AssertionResult, TEST_F, Tes...

class DefaultRallyFixture : public ::testing::Test
{
  protected:
    Rally unit{};
};

TEST_F(DefaultRallyFixture, DefaultConstructor)
{
    EXPECT_TRUE(unit.GetStartTime().isNull());
    EXPECT_TRUE(unit.GetActions().empty());
}

TEST_F(DefaultRallyFixture, SetStartTime)
{
    const QTime& arbitrary_time{9, 37, 20, 333};
    unit.SetStartTime(arbitrary_time);
    EXPECT_EQ(arbitrary_time, unit.GetStartTime());
}

class ExampleRallyFixture : public ::testing::Test
{
  protected:
    const QTime arbitrary_start_time{9, 37, 20, 333};
    Rally unit{arbitrary_start_time};
};

TEST_F(ExampleRallyFixture, Constructor)
{
    EXPECT_EQ(arbitrary_start_time, unit.GetStartTime());
}

TEST_F(ExampleRallyFixture, WriteRallyToFile)
{
    static const char* const filename = "/home/hannes/workspace/data.yaml";

    cv::FileStorage file_storage(filename, cv::FileStorage::WRITE);
    file_storage << "rally" << unit;
    file_storage.release();

    Rally rallyFromFile;
    file_storage.open(filename, cv::FileStorage::READ);
    file_storage["rally"] >> rallyFromFile;
    file_storage.release();

    EXPECT_EQ(unit.GetStartTime(), rallyFromFile.GetStartTime());
}
