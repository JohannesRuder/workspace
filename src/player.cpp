//
// Created by hannes on 11.02.18.
//

#include "player.h"

Player::Player() : name(""), number(0), position(Position::UNDEFINED), numberOfActions(0) {}

Player::Player(std::string nameToBeSet, int numberToBeSet, Position positionToBeSet)
{
    name = nameToBeSet;
    number = numberToBeSet;
    position = positionToBeSet;
    numberOfActions = 0;
}

std::string Player::getName()
{
    return name;
}

int Player::getNumber()
{
    return number;
}

Position Player::getPosition()
{
    return position;
}

int Player::getNumberOfActions()
{
    return numberOfActions;
}

void Player::incrementNumberOfActions()
{
    numberOfActions++;
}

void Player::write(cv::FileStorage& fs) const
{
    fs << "{"
       << "name" << name << "number" << number << "numberOfActions" << numberOfActions << "}";
}  // TODO write position
