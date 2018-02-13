//
// Created by hannes on 13.02.18.
//

#ifndef WORKSPACE_VIDEO_H
#define WORKSPACE_VIDEO_H

#include <opencv2/core/core.hpp>
#include "camera.h"

class Video
{
  private:
    std::string name_;
    std::string filename_;
    Camera camera_;
    cv::Mat gym_floor_mask_;

  public:
    Video();

    void SetName(const std::string& name);
    const std::string& GetName() const;

    void SetFilename(const std::string& filename);
    const std::string& GetFilename() const;
    void SetGymFloorMask(const cv::Mat& mask);
    const cv::Mat& GetGymFloorMask() const;

    void Write(cv::FileStorage& file_storage) const;
    void Read(const cv::FileNode& node);
};

static void write(cv::FileStorage& file_storage, const std::string&, const Video& x)
{
    x.Write(file_storage);
}

static void read(const cv::FileNode& node, Video& x, const Video& default_value = Video())
{
    if (node.empty())
        x = default_value;
    else
        x.Read(node);
}

#endif  // WORKSPACE_VIDEO_H
