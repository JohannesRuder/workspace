//
// Created by hannes on 13.02.18.
//

#ifndef VIDEO_H_
#define VIDEO_H_

#include <string>                        // for string
#include <opencv2/core/mat.hpp>          // for Mat
#include <opencv2/core/mat.inl.hpp>      // for Mat::operator=, Mat::~Mat
#include <opencv2/core/persistence.hpp>  // for FileStorage (ptr only), File...

#include "camera.h"  // for Camera

class Video
{
  private:
    std::string name_;
    std::string filename_;
    Camera camera_;
    cv::Mat gym_floor_mask_;

  public:
    Video() = default;
    Video(const std::string& name, const std::string& filename);

    void SetName(const std::string& name);
    const std::string& GetName() const;

    void SetFilename(const std::string& filename);
    const std::string& GetFilename() const;

    const Camera& GetCamera() const;

    void SetGymFloorMask(const cv::Mat& mask);
    const cv::Mat& GetGymFloorMask() const;

    bool operator==(const Video& rhs) const;

    void Write(cv::FileStorage& file_storage) const;
    void Read(const cv::FileNode& node);
};

inline void write(cv::FileStorage& file_storage, const std::string&, const Video& x)
{
    x.Write(file_storage);
}

inline void read(const cv::FileNode& node, Video& x, const Video& default_value = Video())
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

#endif  // VIDEO_H_
