//
// Created by hannes on 18.02.18.
//

#include "gym.h"

Gym::Gym() : name_(""), address_(""), line_color_(), floor_color_() {}

void Gym::Write(cv::FileStorage& file_storage) const
{
    file_storage << "{"
                 << "name" << name_ << "address"
                 << address_
                 //<< "lineColor" << lineColor
                 //<< "floorColor" << floorColor
                 << "}";
    // TODO: Write line and floor colors
}

void Gym::Read(const cv::FileNode& node)
{
    name_ = static_cast<std::string>(node["name"]);
    address_ = static_cast<std::string>(node["address"]);
    // TODO: Read line and floor colors
}
