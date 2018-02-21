//
// Created by hannes on 15.02.18.
//

#include "action.h"
#include <QDebug>

Action::Action() : time_() {}

void Action::Write(cv::FileStorage& file_storage) const
{
    file_storage << "{"
                 << "time" << time_.toString("hh:mm:ss:zzz").toStdString() << "}";
}

void Action::Read(const cv::FileNode& node)
{
    std::string temp_std_string = static_cast<std::string>(node["time"]);
    QString temp_q_string = QString::fromStdString(temp_std_string);
    time_ = QTime::fromString(temp_q_string, "hh:mm:ss:zzz");
}

const QTime& Action::GetTime() const
{
    return time_;
}

void Action::SetTime(const QTime& time)
{
    time_ = time;
}

Action::Action(const QTime& time) : time_(time) {}

bool Action::operator==(const Action& rhs) const
{
    return time_ == rhs.time_;
}