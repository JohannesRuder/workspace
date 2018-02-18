//
// Created by hannes on 15.02.18.
//

#ifndef WORKSPACE_ACTION_H
#define WORKSPACE_ACTION_H

#include <opencv2/core/core.hpp>
#include "player.h"
#include <qt5/QtCore/QString>
#include <qt5/QtCore/QTime>
#include <qt5/QtCore/Qt>

class Action
{
  private:
    QTime time_;

  public:
    Action();
    Action(const QTime& time);

    const QTime& GetTime() const;
    void SetTime(const QTime& time);

    bool operator==(const Action& rhs) const;

    void Write(cv::FileStorage& file_storage) const;
    void Read(const cv::FileNode& node);
};

inline void write(cv::FileStorage& file_storage, const std::string&, const Action& x)
{
    x.Write(file_storage);
}

inline void read(const cv::FileNode& node, Action& x, const Action& default_value = Action())
{
    if (node.empty())
        x = default_value;
    else
        x.Read(node);
}

#endif  // WORKSPACE_ACTION_H
