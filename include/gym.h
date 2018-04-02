//
// Created by hannes on 18.02.18.
//

#ifndef GYM_H_
#define GYM_H_

#include "../../../../usr/include/c++/5/string"                        // for string, basic_string
#include "../../../../usr/local/include/opencv2/core/persistence.hpp"  // for FileStorage (ptr only), File...
#include "../../../../usr/include/x86_64-linux-gnu/qt5/QtGui/qcolor.h"                      // for QColor

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

#endif  // GYM_H_
