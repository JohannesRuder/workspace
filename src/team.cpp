//
// Created by hannes on 11.02.18.
//

#include "team.h"

Team::Team() : name(""), playerVector(0) {}

Team::Team(std::string nameToBeSet) : name(nameToBeSet) {}

void Team::setTeam(std::string nameToBeSet)
{
    name = nameToBeSet;
}

std::string Team::getName()
{
    return name;
}

Player Team::getPlayer(int playerNumber)
{
    return playerVector[playerNumber];
}

void Team::addPlayer(Player playerToBeAdded)
{
    playerVector.push_back(playerToBeAdded);
}

void Team::write(cv::FileStorage& fs) const
{
    fs << "{"
       << "name" << name << "}";
}
