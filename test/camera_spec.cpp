//
// Created by hannes on 13.02.18.
//

#include "../src/camera.h"
#include "gtest/gtest.h"

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

TEST(ExampleCamera, Constructor)
{
    const std::string example_camera_name{"GoPro Hero4"};
    const std::string example_camera_calibration_file{"/home/hannes/workspace/test/example_camera_calibration.yaml"};

    Camera unit{example_camera_name, example_camera_calibration_file};

    EXPECT_EQ(example_camera_name, unit.GetName());
    EXPECT_EQ(example_camera_calibration_file, unit.GetCameraCalibrationFilename());
    EXPECT_FALSE(unit.GetIntrinsics().empty());
    EXPECT_FALSE(unit.GetDistortion().empty());
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
