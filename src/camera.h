//
// Created by hannes on 13.02.18.
//

#ifndef WORKSPACE_CAMERA_H
#define WORKSPACE_CAMERA_H

#include <opencv2/core/core.hpp>

class Camera
{
  private:
    std::string name_;
    std::string camera_calibration_filename_;
    cv::Mat intrinsics_;
    cv::Mat distortion_;

  public:
    Camera();
    Camera(const std::string& name, const std::string& camera_calibration_filename);

    void SetName(const std::string& name);
    const std::string& GetName() const;
    void SetCameraCalibrationFilename(const std::string& filename);
    const std::string& GetCameraCalibrationFilename() const;
    void ReadCameraCalibrationFile();
    const cv::Mat& GetIntrinsics() const;
    const cv::Mat& GetDistortion() const;

    void Write(cv::FileStorage& file_storage) const;
    void Read(const cv::FileNode& node);
};

static void write(cv::FileStorage& file_storage, const std::string&, const Camera& x)
{
    x.Write(file_storage);
}

static void read(const cv::FileNode& node, Camera& x, const Camera& default_value = Camera())
{
    if (node.empty())
        x = default_value;
    else
        x.Read(node);
}

#endif  // WORKSPACE_CAMERA_H