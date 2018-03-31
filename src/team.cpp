//
// Created by hannes on 11.02.18.
//

#include "team.h"

#include <opencv2/core/cvstd.inl.hpp>  // for operator<<, String::operator b...

Team::Team() : name_(""), players_(0) {}

Team::Team(const QString& name) : name_(name) {}

const QString& Team::GetName() const
{
    return name_;
}

const Player& Team::GetPlayer(int player_number) const
{
    return players_[player_number];
}

void Team::AddPlayer(const Player& player)
{
    players_.push_back(player);
}

void Team::SetName(const QString& name)
{
    name_ = name;
}

void Team::Write(cv::FileStorage& file_storage) const
{
    file_storage << "{"
                 << "name" << name_.toStdString() << "players" << players_ << "}";
}

const std::vector<Player>& Team::GetPlayers() const
{
    return players_;
}

void Team::Read(const cv::FileNode& node)
{
    name_ = QString::fromStdString(static_cast<std::string>(node["name"]));

    auto file_node = node["players"];
    for (auto&& iterator : file_node)
    {
        Player player;
        iterator >> player;
        players_.push_back(player);
    }
}

bool Team::operator==(const Team& rhs) const
{
    return name_ == rhs.name_ && players_ == rhs.players_;
}
