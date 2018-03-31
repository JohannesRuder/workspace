//
// Created by hannes on 15.02.18.
//

#include "rally.h"

#include <qstring.h>  // for QString

Rally::Rally() : start_time_(), actions_() {}

Rally::Rally(const QTime& start_time) : start_time_(start_time) {}

const QTime& Rally::GetStartTime() const
{
    return start_time_;
}

void Rally::SetStartTime(const QTime& start_time)
{
    start_time_ = start_time;
}

const std::vector<Action>& Rally::GetActions() const
{
    return actions_;
}

void Rally::AddAction(const Action& action)
{
    actions_.push_back(action);
}

void Rally::Write(cv::FileStorage& file_storage) const
{
    file_storage << "{"
                 << "start_time" << start_time_.toString("hh:mm:ss:zzz").toStdString() << "actions" << actions_ << "}";
}

void Rally::Read(const cv::FileNode& node)
{
    auto temp_std_string = static_cast<std::string>(node["start_time"]);
    auto temp_q_string = QString::fromStdString(temp_std_string);
    start_time_ = QTime::fromString(temp_q_string, "hh:mm:ss:zzz");

    auto file_node = node["actions"];
    file_node >> actions_;
}

bool Rally::operator==(const Rally& rhs) const
{
    return start_time_ == rhs.start_time_ && actions_ == rhs.actions_;
}
