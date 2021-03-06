//
// Created by hannes on 13.02.18.
//

#ifndef CAMERA_H_
#define CAMERA_H_

#include "opencv2/core/mat.hpp"          // for
#include "opencv2/core/mat.inl.hpp"      // for Mat::operator=, Mat::~Mat
#include <string>                        // for string, basic_string
#include "opencv2/core/persistence.hpp"

class Camera
{
  private:
    std::string name_;
    std::string camera_calibration_filename_;
    cv::Mat intrinsics_;
    cv::Mat distortion_;

  public:
    Camera() = default;
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

    bool operator==(Camera camera_to_compare) const;
};

inline void write(cv::FileStorage& file_storage, const std::string&, const Camera& x)
{
    x.Write(file_storage);
}

inline void read(const cv::FileNode& node, Camera& x, const Camera& default_value = Camera())
{
    if (node.empty())
    {
        x = default_value;
    }
    else
    {
        x.Read(node);
    }
}

#endif  // CAMERA_H_
