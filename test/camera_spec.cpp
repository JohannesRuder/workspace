//
// Created by hannes on 13.02.18.
//

#include "../src/camera.h"
#include <gtest/gtest.h>

class DefaultCameraFixture : public ::testing::Test
{
protected:
    Camera unit{};
};

TEST_F(DefaultCameraFixture, DefaultConstructor)
{
    EXPECT_EQ("", unit.GetName());
    EXPECT_EQ("", unit.GetCameraCalibrationFilename());
    EXPECT_TRUE(unit.GetIntrinsics().empty());
    EXPECT_TRUE(unit.GetDistortion().empty());
}

TEST_F(DefaultCameraFixture, SetName)
{
    const std::string arbitrary_camera_name{"GoPro Hero4"};
    unit.SetName(arbitrary_camera_name);

    EXPECT_EQ(arbitrary_camera_name, unit.GetName());
}

TEST_F(DefaultCameraFixture, SetCameraCalibrationFile)
{
    const std::string example_camera_calibration_file{"/home/hannes/workspace/test/example_camera_calibration.yaml"};
    unit.SetCameraCalibrationFilename(example_camera_calibration_file);

    EXPECT_EQ(example_camera_calibration_file, unit.GetCameraCalibrationFilename());
    EXPECT_FALSE(unit.GetIntrinsics().empty());
    EXPECT_FALSE(unit.GetDistortion().empty());
}

class ExampleCameraFixture : public ::testing::Test
{
protected:
    const std::string example_video_name{"GoPro Hero4"};
    const std::string example_video_filename{"/home/hannes/workspace/test/example_camera_calibration.yaml"};

    Camera unit{example_video_name, example_video_filename};
};

TEST_F(ExampleCameraFixture, Constructor)
{
    EXPECT_EQ(example_video_name, unit.GetName());
    EXPECT_EQ(example_video_filename, unit.GetCameraCalibrationFilename());
    EXPECT_FALSE(unit.GetIntrinsics().empty());
    EXPECT_FALSE(unit.GetDistortion().empty());
}

TEST_F(ExampleCameraFixture, FileInAndOutput)
{
    static const char* const filename = "/home/hannes/workspace/data.yaml";

    cv::FileStorage file_storage(filename, cv::FileStorage::WRITE);
    file_storage << "camera" << unit;
    file_storage.release();

    Camera camera_from_file;
    file_storage.open(filename, cv::FileStorage::READ);
    file_storage["camera"] >> camera_from_file;
    file_storage.release();

    EXPECT_EQ(unit.GetName(), camera_from_file.GetName());
    EXPECT_EQ(unit.GetCameraCalibrationFilename(), camera_from_file.GetCameraCalibrationFilename());
    // TODO: Compare intrinsics and distortion
}

TEST_F(ExampleCameraFixture, CompareCameras_AllEqual)
{
    Camera camera{example_video_name, example_video_filename};
    EXPECT_TRUE(unit == camera);
}

TEST_F(ExampleCameraFixture, CompareCameras_DifferentName)
{
    Camera camera{"Different name", example_video_filename};
    EXPECT_FALSE(unit == camera);
}

TEST_F(ExampleCameraFixture, CompareCameras_DifferentVideoFilename)
{
    Camera camera{example_video_name, "Different video filename"};
    EXPECT_FALSE(unit == camera);
}
