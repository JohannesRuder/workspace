//
// Created by hannes on 17.02.18.
//

#include <gtest/gtest-message.h>         // for Message
#include <gtest/gtest-test-part.h>       // for TestPartResult
#include <opencv2/core/persistence.hpp>  // for FileStorage, operator<<, ope...
#include <vector>                        // for vector

#include "set.h"                  // for Set
#include "gtest/gtest_pred_impl.h"       // for EXPECT_EQ, AssertionResult

class DefaultSetFixture : public ::testing::Test
{
  protected:
    Set unit_{};
};

TEST_F(DefaultSetFixture, DefaultConstructor)
{
    EXPECT_EQ(0, unit_.GetHomeScore());
    EXPECT_EQ(0, unit_.GetGuestScore());
    EXPECT_TRUE(unit_.GetRallies().empty());
}

TEST_F(DefaultSetFixture, IncrementHomeScore)
{
    EXPECT_EQ(0, unit_.GetHomeScore());
    unit_.IncrementHomeScore();
    EXPECT_EQ(1, unit_.GetHomeScore());
}

TEST_F(DefaultSetFixture, IncrementGuestScore)
{
    EXPECT_EQ(0, unit_.GetGuestScore());
    unit_.IncrementGuestScore();
    EXPECT_EQ(1, unit_.GetGuestScore());
}

TEST_F(DefaultSetFixture, WriteSetToFile)
{
    static const char *const filename = "/home/hannes/workspace/data.yaml";

    cv::FileStorage file_storage(filename, cv::FileStorage::WRITE);
    file_storage << "set" << unit_;
    file_storage.release();

    Set set_from_file;
    file_storage.open(filename,cv::FileStorage::READ);
    file_storage["set"] >> set_from_file;
    file_storage.release();

    EXPECT_EQ(unit_.GetHomeScore(), set_from_file.GetHomeScore());
    EXPECT_EQ(unit_.GetGuestScore(), set_from_file.GetGuestScore());
    // TODO: Compare Rallies
}
