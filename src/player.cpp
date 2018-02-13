//
// Created by hannes on 11.02.18.
//

#include "player.h"

Player::Player() : name_(""), number_(0), position_(Position::UNDEFINED), number_of_actions_(0) {}

Player::Player(std::string name, int number, Position position)
{
    name_ = name;
    number_ = number;
    position_ = position;
    number_of_actions_ = 0;
}

const std::string& Player::GetName() const
{
    return name_;
}

const int& Player::GetNumber() const
{
    return number_;
}

const Position& Player::GetPosition() const
{
    return position_;
}

const int& Player::GetNumberOfActions() const
{
    return number_of_actions_;
}

void Player::IncrementNumberOfActions()
{
    number_of_actions_++;
}

void Player::Write(cv::FileStorage& file_storage) const
{
    file_storage << "{"
                 << "name" << name_ << "number" << number_ << "numberOfActions" << number_of_actions_ << "}";
}

void Player::Read(const cv::FileNode& node)
{
    name_ = (std::string)node["name"];
    number_ = (int)node["number"];
    number_of_actions_ = (int)node["numberOfActions"];
}

bool Player::operator==(Player player_to_compare) const
{
    return this->GetName() == player_to_compare.GetName() && this->GetNumber() == player_to_compare.GetNumber();
}
