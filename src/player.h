//
// Created by hannes on 11.02.18.
//

#ifndef WORKSPACE_PLAYER_H
#define WORKSPACE_PLAYER_H

#include <opencv2/core/core.hpp>

enum class Position
{
    STELLER,
    MITTELBLOCKER,
    AUSSENANGREIFER,
    UNDEFINED
};

class Player
{
  private:
    std::string name;
    int number;
    Position position;
    int numberOfActions;

  public:
    Player();
    Player(std::string nameToBeSet, int numberToBeSet, Position positionToBeSet);
    std::string getName();
    int getNumber();
    Position getPosition();
    int getNumberOfActions();
    void incrementNumberOfActions();

    void write(cv::FileStorage& fs) const;
};

static void write(cv::FileStorage& fs, const std::string&, const Player& x)
{
    x.write(fs);
}

#endif  // WORKSPACE_PLAYER_H
