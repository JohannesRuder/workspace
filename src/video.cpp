//
// Created by hannes on 13.02.18.
//

#include "video.h"

Video::Video() : name_(""), filename_(""), camera_(), gym_floor_mask_() {}

void Video::SetName(const std::string& name)
{
    name_ = name;
}

const std::string& Video::GetName() const
{
    return name_;
}

void Video::SetFilename(const std::string& filename)
{
    filename_ = filename;
}

const std::string& Video::GetFilename() const
{
    return filename_;
}

void Video::SetGymFloorMask(const cv::Mat& mask)
{
    gym_floor_mask_ = mask;
}

const cv::Mat& Video::GetGymFloorMask() const
{
    return gym_floor_mask_;
}

void Video::Write(cv::FileStorage& file_storage) const
{
    file_storage << "{"
                 << "name" << name_ << "filename" << filename_ << "camera" << camera_ << "gym_floor_mask"
                 << gym_floor_mask_ << "}";
}

void Video::Read(const cv::FileNode& node)
{
    name_ = (std::string)node["name"];
    filename_ = (std::string)node["filename"];
    node["camera"] >> camera_;
    node["gym_floor_mask"] >> gym_floor_mask_;
}
