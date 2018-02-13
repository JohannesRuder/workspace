//
// Created by hannes on 13.02.18.
//

#include "camera.h"

Camera::Camera() : name_(""), camera_calibration_filename_(""), intrinsics_(), distortion_() {}

Camera::Camera(const std::string& name, const std::string& camera_calibration_filename)
        : name_(name), camera_calibration_filename_(camera_calibration_filename)
{
    ReadCameraCalibrationFile();
}

void Camera::SetName(const std::string& name)
{
    name_ = name;
}

const std::string& Camera::GetName() const
{
    return name_;
}

void Camera::SetCameraCalibrationFilename(const std::string& filename)
{
    camera_calibration_filename_ = filename;
}

const std::string& Camera::GetCameraCalibrationFilename() const
{
    return camera_calibration_filename_;
}

void Camera::ReadCameraCalibrationFile()
{
    cv::FileStorage file_storage(camera_calibration_filename_, cv::FileStorage::READ);
    file_storage["camera_matrix"] >> intrinsics_;
    file_storage["distortion_coefficients"] >> distortion_;
    file_storage.release();
}

void Camera::Write(cv::FileStorage& file_storage) const
{
    file_storage << "{"
                 << "name" << name_ << "camera_calibration_filename" << camera_calibration_filename_ << "intrinsics"
                 << intrinsics_ << "distortion" << distortion_ << "}";
}

void Camera::Read(const cv::FileNode& node)
{
    name_ = (std::string)node["name"];
    camera_calibration_filename_ = (std::string)node["camera_calibration_filename"];
    node["intrinsics"] >> intrinsics_;
    node["distortion"] >> distortion_;
}

const cv::Mat& Camera::GetIntrinsics() const
{
    return intrinsics_;
}

const cv::Mat& Camera::GetDistortion() const
{
    return distortion_;
}
