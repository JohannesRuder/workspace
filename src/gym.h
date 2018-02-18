//
// Created by hannes on 18.02.18.
//

#ifndef WORKSPACE_GYM_H
#define WORKSPACE_GYM_H

#include <opencv2/core/core.hpp>
#include <QColor>
#include <QString>

class Gym
{
  private:
    std::string name_;
    std::string address_;
    QColor line_color_;
    QColor floor_color_;

  public:
    Gym();

    void Write(cv::FileStorage& file_storage) const;
    void Read(const cv::FileNode& node);
};

inline void write(cv::FileStorage& file_storage, const std::string&, const Gym& x)
{
    x.Write(file_storage);
}

inline void read(const cv::FileNode& node, Gym& x, const Gym& default_value = Gym())
{
    if (node.empty())
        x = default_value;
    else
        x.Read(node);
}

#endif  // WORKSPACE_GYM_H
