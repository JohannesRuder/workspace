//
// Created by hannes on 11.02.18.
//

#include "team.h"

Team::Team() : name_(""), players_(0) {}

Team::Team(std::string name) : name_(name) {}

const std::string& Team::GetName() const
{
    return name_;
}

const Player& Team::GetPlayer(int player_number) const
{
    return players_[player_number];
}

void Team::AddPlayer(Player player)
{
    players_.push_back(player);
}

void Team::Write(cv::FileStorage& file_storage) const
{
    file_storage << "{"
                 << "name" << name_ << "}";
}

void Team::SetName(const std::string& name)
{
    Team::name_ = name;
}
