//
// Created by hannes on 14.02.18.
//

#include <gtest/gtest-message.h>         // for Message
#include <gtest/gtest-test-part.h>       // for TestPartResult
#include "opencv2/core/mat.hpp"          // for Mat
#include "opencv2/core/mat.inl.hpp"      // for Mat::empty
#include "opencv2/core/persistence.hpp"  // for FileStorage, operator<<, ope...
#include <string>                        // for string

#include "mylib/camera.h"               // for Camera
#include "mylib/video.h"                // for Video
#include "gtest/gtest_pred_impl.h"       // for AssertionResult, EXPECT_EQ

class DefaultVideoFixture : public ::testing::Test
{
  protected:
    Video unit_{};
};

TEST_F(DefaultVideoFixture, DefaultConstructor)
{
    EXPECT_EQ("", unit_.GetName());
    EXPECT_EQ("", unit_.GetFilename());
    EXPECT_EQ(Camera{}, unit_.GetCamera());
    EXPECT_TRUE(unit_.GetGymFloorMask().empty());
}

TEST_F(DefaultVideoFixture, SetName)
{
    const std::string arbitrary_video_name{"Los Krachos vs. Nix Is Fix"};
    unit_.SetName(arbitrary_video_name);

    EXPECT_EQ(arbitrary_video_name, unit_.GetName());
}

TEST_F(DefaultVideoFixture, SetFilename)
{
    const std::string example_video_filename{"/home/hannes/workspace/test/2016-02-15_NixIsFix.mp4"};
    unit_.SetFilename(example_video_filename);

    EXPECT_EQ(example_video_filename, unit_.GetFilename());
}

class ExampleVideoFixture : public ::testing::Test
{
  protected:
    const std::string example_video_name{"Los Krachos vs. Nix Is Fix"};
    const std::string example_video_filename{"/home/hannes/workspace/test/2016-02-15_NixIsFix.mp4"};

    Video unit_{example_video_name, example_video_filename};
};

TEST_F(ExampleVideoFixture, Constructor)
{
    EXPECT_EQ(example_video_name, unit_.GetName());
    EXPECT_EQ(example_video_filename, unit_.GetFilename());
    EXPECT_EQ(Camera{}, unit_.GetCamera());
    EXPECT_TRUE(unit_.GetGymFloorMask().empty());
}

TEST_F(ExampleVideoFixture, FileInAndOutput)
{
    static const char* const filename = "/home/hannes/workspace/data.yaml";

    cv::FileStorage file_storage(filename, cv::FileStorage::WRITE);
    file_storage << "video" << unit_;
    file_storage.release();

    Video video_from_file;
    file_storage.open(filename, cv::FileStorage::READ);
    file_storage["video"] >> video_from_file;
    file_storage.release();

    EXPECT_EQ(unit_.GetName(), video_from_file.GetName());
    EXPECT_EQ(unit_.GetFilename(), video_from_file.GetFilename());
}
