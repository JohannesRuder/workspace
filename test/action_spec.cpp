//
// Created by hannes on 16.02.18.
//

#include <gtest/gtest-message.h>         // for Message
#include <gtest/gtest-test-part.h>       // for TestPartResult
#include <opencv2/core/persistence.hpp>  // for FileStorage, operator<<, ope...
#include <qdatetime.h>                   // for QTime

#include "action.h"                 // for Action
#include "gtest/gtest_pred_impl.h"  // for AssertionResult, TEST_F, Tes...

class DefaultActionFixture : public ::testing::Test
{
  protected:
    Action unit_{};
};

TEST_F(DefaultActionFixture, DefaultConstructor)
{
    EXPECT_TRUE(unit_.GetTime().isNull());
}

TEST_F(DefaultActionFixture, SetTime)
{
    const QTime& arbitrary_time{9, 37, 20, 333};
    unit_.SetTime(arbitrary_time);
    EXPECT_EQ(arbitrary_time, unit_.GetTime());
}

class ExampleActionFixture : public ::testing::Test
{
  protected:
    const QTime arbitrary_time{9, 37, 20, 333};
    Action unit_{arbitrary_time};
};

TEST_F(ExampleActionFixture, Constructor)
{
    EXPECT_EQ(arbitrary_time, unit_.GetTime());
}

TEST_F(ExampleActionFixture, WriteActionToFile)
{
    static const char* const filename = "/home/hannes/workspace/data.yaml";

    cv::FileStorage file_storage(filename, cv::FileStorage::WRITE);
    file_storage << "action" << unit_;
    file_storage.release();

    Action action_from_file;
    file_storage.open(filename, cv::FileStorage::READ);
    file_storage["action"] >> action_from_file;
    file_storage.release();

    EXPECT_EQ(unit_.GetTime(), action_from_file.GetTime());
}
