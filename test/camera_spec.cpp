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
    std::string example_camera_name{"GoPro Hero4"};
    std::string example_camera_calibration_file{"/home/hannes/workspace/test/example_camera_calibration.yaml"};

    Camera unit{example_camera_name, example_camera_calibration_file};

    EXPECT_EQ(example_camera_name, unit.GetName());
    EXPECT_EQ(example_camera_calibration_file, unit.GetCameraCalibrationFilename());
    EXPECT_FALSE(unit.GetIntrinsics().empty());
    EXPECT_FALSE(unit.GetDistortion().empty());
}
