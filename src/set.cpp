//
// Created by hannes on 15.02.18.
//

#include "set.h"

void Set::Write(cv::FileStorage& file_storage) const
{
    file_storage << "{"
                 << "homeScore" << home_score_ << "guestScore" << guest_score_ << "}";
}

void Set::Read(const cv::FileNode& node)
{
    home_score_ = static_cast<int>(node["homeScore"]);
    guest_score_ = static_cast<int>(node["guestScore"]);
}

int Set::GetHomeScore() const
{
    return home_score_;
}

int Set::GetGuestScore() const
{
    return guest_score_;
}

void Set::IncrementHomeScore()
{
    home_score_++;
}

void Set::IncrementGuestScore()
{
    guest_score_++;
}

const std::vector<Rally>& Set::GetRallies() const
{
    return rallies_;
}

bool Set::operator==(const Set& rhs) const
{
    return home_score_ == rhs.home_score_ && guest_score_ == rhs.guest_score_ && rallies_ == rhs.rallies_;
}
