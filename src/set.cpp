//
// Created by hannes on 15.02.18.
//

#include "set.h"

Set::Set() : homeScore_(0), guestScore_(0), rallies_(0) {}

void Set::Write(cv::FileStorage& file_storage) const
{
    file_storage << "{"
                 << "homeScore" << homeScore_ << "guestScore" << guestScore_ << "}";
}

void Set::Read(const cv::FileNode& node)
{
    homeScore_ = static_cast<int>(node["homeScore"]);
    guestScore_ = static_cast<int>(node["guestScore"]);
}

int Set::GetHomeScore() const
{
    return homeScore_;
}

int Set::GetGuestScore() const
{
    return guestScore_;
}

void Set::IncrementHomeScore()
{
    homeScore_++;
}

void Set::IncrementGuestScore()
{
    guestScore_++;
}

const std::vector<Rally>& Set::GetRallies() const
{
    return rallies_;
}

bool Set::operator==(const Set& rhs) const
{
    return homeScore_ == rhs.homeScore_ && guestScore_ == rhs.guestScore_ && rallies_ == rhs.rallies_;
}
