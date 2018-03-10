//
// Created by hannes on 13.02.18.
//

#include <gtest/gtest.h>
#include "../src/camera.h"
#include <QtGui/QtGui>

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
    const auto arbitrary_camera_name{"GoPro Hero4"};
    unit.SetName(arbitrary_camera_name);

    EXPECT_EQ(arbitrary_camera_name, unit.GetName());
}

TEST_F(DefaultCameraFixture, SetCameraCalibrationFile)
{
    const std::string example_camera_calibration_file{"/home/hannes/workspace/test/example_camera_calibration.yaml"};
    unit.SetCameraCalibrationFilename(example_camera_calibration_file);

    cv::Mat intrinsics_from_example_camera_calibration_file;
    intrinsics_from_example_camera_calibration_file = (cv::Mat_<double>(3, 3) << 6.5746697810243404e+002,
                                                       0.0,
                                                       3.1950000000000000e+002,
                                                       0.0,
                                                       6.5746697810243404e+002,
                                                       2.3950000000000000e+002,
                                                       0.0,
                                                       0.0,
                                                       1.0);

    cv::Mat distortion_from_example_camera_calibration_file;
    distortion_from_example_camera_calibration_file = (cv::Mat_<double>(5, 1) << -4.1802327018241026e-001,
                                                       5.0715243805833121e-001,
                                                       0.0,
                                                       0.0,
                                                       -5.7843596847939704e-001);

    EXPECT_EQ(example_camera_calibration_file, unit.GetCameraCalibrationFilename());
    EXPECT_TRUE(IsMatEqual(intrinsics_from_example_camera_calibration_file, unit.GetIntrinsics()));
    EXPECT_TRUE(IsMatEqual(distortion_from_example_camera_calibration_file, unit.GetDistortion()));
}

class ExampleCameraFixture : public ::testing::Test
{
  protected:
    const std::string example_camera_name{"GoPro Hero4"};
    const std::string example_camera_calibration_file{"/home/hannes/workspace/test/example_camera_calibration.yaml"};

    Camera unit{example_camera_name, example_camera_calibration_file};
};

TEST_F(ExampleCameraFixture, Constructor)
{
    cv::Mat intrinsics_from_example_camera_calibration_file;
    intrinsics_from_example_camera_calibration_file = (cv::Mat_<double>(3, 3) << 6.5746697810243404e+002,
            0.0,
            3.1950000000000000e+002,
            0.0,
            6.5746697810243404e+002,
            2.3950000000000000e+002,
            0.0,
            0.0,
            1.0);

    cv::Mat distortion_from_example_camera_calibration_file;
    distortion_from_example_camera_calibration_file = (cv::Mat_<double>(5, 1) << -4.1802327018241026e-001,
            5.0715243805833121e-001,
            0.0,
            0.0,
            -5.7843596847939704e-001);

    EXPECT_EQ(example_camera_name, unit.GetName());
    EXPECT_EQ(example_camera_calibration_file, unit.GetCameraCalibrationFilename());
    EXPECT_TRUE(IsMatEqual(intrinsics_from_example_camera_calibration_file, unit.GetIntrinsics()));
    EXPECT_TRUE(IsMatEqual(distortion_from_example_camera_calibration_file, unit.GetDistortion()));
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
    EXPECT_TRUE(IsMatEqual(unit.GetIntrinsics(), camera_from_file.GetIntrinsics()));
    EXPECT_TRUE(IsMatEqual(unit.GetDistortion(), camera_from_file.GetDistortion()));
}

TEST_F(ExampleCameraFixture, CompareCameras_AllEqual)
{
    Camera camera{example_camera_name, example_camera_calibration_file};
    EXPECT_TRUE(unit == camera);
}

TEST_F(ExampleCameraFixture, CompareCameras_DifferentCameraName)
{
    Camera camera{"Different name", example_camera_name};
    EXPECT_FALSE(unit == camera);
}

TEST_F(ExampleCameraFixture, CompareCameras_DifferentCameraCalibrationFilename)
{
    Camera camera{example_camera_calibration_file, "Different camera calibration filename"};
    EXPECT_FALSE(unit == camera);
}
