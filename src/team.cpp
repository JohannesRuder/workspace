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

void Team::SetName(const std::string& name)
{
    Team::name_ = name;
}

void Team::Write(cv::FileStorage& file_storage) const
{
    file_storage << "{"
                 << "name" << name_ << "players" << players_ << "}";
}

const std::vector<Player>& Team::GetPlayers() const
{
    return players_;
}

void Team::Read(const cv::FileNode& node)
{
    name_ = (std::string)node["name"];

    cv::FileNode file_node = node["players"];
    for (cv::FileNodeIterator iterator = file_node.begin(); iterator != file_node.end(); ++iterator)
    {
        cv::FileNode node = *iterator;
        Player player;
        node >> player;
        players_.push_back(player);
    }
}
