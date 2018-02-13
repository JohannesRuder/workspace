//
// Created by hannes on 11.02.18.
//

#ifndef WORKSPACE_TEAM_H
#define WORKSPACE_TEAM_H

#include <opencv2/core/core.hpp>
#include "player.h"

class Team
{

  private:
    std::string name_;
    std::vector<Player> players_;

  public:
    explicit Team();
    explicit Team(std::string name);

    void SetName(const std::string& name);
    const std::string& GetName() const;

    void AddPlayer(Player player);
    const std::vector<Player>& GetPlayers() const;
    const Player& GetPlayer(int player_number) const;

    void Write(cv::FileStorage& file_storage) const;
    void Read(const cv::FileNode& node);
};

static void write(cv::FileStorage& file_storage, const std::string&, const Team& x)
{
    x.Write(file_storage);
}

static void read(const cv::FileNode& node, Team& x, const Team& default_value = Team())
{
    if (node.empty())
        x = default_value;
    else
        x.Read(node);
}

#endif  // WORKSPACE_TEAM_H
