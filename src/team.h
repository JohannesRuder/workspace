//
// Created by hannes on 11.02.18.
//

#ifndef WORKSPACE_TEAM_H
#define WORKSPACE_TEAM_H

#include "player.h"

class Team
{

  private:
    std::string name;
    std::vector<Player> playerVector;

  public:
    explicit Team();
    explicit Team(std::string nameToBeSet);

    void setTeam(std::string name);
    std::string getName();
    Player getPlayer(int playerNumber);
    void addPlayer(Player playerToBeAdded);

    void write(cv::FileStorage& fs) const;
};

static void write(cv::FileStorage& fs, const std::string&, const Team& x)
{
    x.write(fs);
}

#endif  // WORKSPACE_TEAM_H
