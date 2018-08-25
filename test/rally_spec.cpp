//
// Created by hannes on 16.02.18.
//

#include <vector>                        // for vector
#include <gtest/gtest-message.h>         // for Message
#include <gtest/gtest-test-part.h>       // for TestPartResult
#include <opencv2/core/persistence.hpp>  // for FileStorage, operator<<, ope...
#include <qdatetime.h>                   // for QTime

#include "gtest/gtest_pred_impl.h"  // for AssertionResult, TEST_F, Tes...
#include "rally.h"                  // for Rally

class DefaultRallyFixture : public ::testing::Test
{
  protected:
    Rally unit_{};
};

TEST_F(DefaultRallyFixture, DefaultConstructor)
{
    EXPECT_TRUE(unit_.GetStartTime().isNull());
    EXPECT_TRUE(unit_.GetActions().empty());
}

TEST_F(DefaultRallyFixture, SetStartTime)
{
    const QTime& arbitrary_time{9, 37, 20, 333};
    unit_.SetStartTime(arbitrary_time);
    EXPECT_EQ(arbitrary_time, unit_.GetStartTime());
}

class ExampleRallyFixture : public ::testing::Test
{
  protected:
    const QTime arbitrary_start_time{9, 37, 20, 333};
    Rally unit_{arbitrary_start_time};
};

TEST_F(ExampleRallyFixture, Constructor)
{
    EXPECT_EQ(arbitrary_start_time, unit_.GetStartTime());
}

TEST_F(ExampleRallyFixture, WriteRallyToFile)
{
    static const char* const filename = "/home/hannes/workspace/data.yaml";

    cv::FileStorage file_storage(filename, cv::FileStorage::WRITE);
    file_storage << "rally" << unit_;
    file_storage.release();

    Rally rally_from_file;
    file_storage.open(filename, cv::FileStorage::READ);
    file_storage["rally"] >> rally_from_file;
    file_storage.release();

    EXPECT_EQ(unit_.GetStartTime(), rally_from_file.GetStartTime());
}
