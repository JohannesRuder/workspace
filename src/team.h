//
// Created by hannes on 11.02.18.
//

#ifndef WORKSPACE_TEAM_H
#define WORKSPACE_TEAM_H

#include "player.h"

class Team
{

  private:
    std::string name_;
    std::vector<Player> players_;

  public:
    explicit Team();
    explicit Team(std::string name);

    const std::string& GetName() const;
    const Player& GetPlayer(int player_number) const;

    void SetName(const std::string& name);

    void AddPlayer(Player player);

    void Write(cv::FileStorage& file_storage) const;
};

static void Write(cv::FileStorage& file_storage, const std::string&, const Team& x)
{
    x.Write(file_storage);
}

#endif  // WORKSPACE_TEAM_H
