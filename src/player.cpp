//
// Created by hannes on 11.02.18.
//

#include "player.h"

Player::Player(const std::string& name, int number, Position position)
    : name_{name}, number_{number}, position_{position}, number_of_actions_{0}
{
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
                 << "name" << name_ << "number" << number_;
    switch (position_)
    {
        case Position::kSTELLER:
            file_storage << "position"
                         << "kSTELLER";
            break;
        case Position::kMITTELBLOCKER:
            file_storage << "position"
                         << "kMITTELBLOCKER";
            break;
        case Position::kAUSSENANGREIFER:
            file_storage << "position"
                         << "kAUSSENANGREIFER";
            break;
        default:
            file_storage << "position"
                         << "UNDEFINED";
    }
    file_storage << "numberOfActions" << number_of_actions_ << "}";
}

void Player::Read(const cv::FileNode& node)
{
    name_ = static_cast<std::string>(node["name"]);
    number_ = static_cast<int>(node["number"]);
    if (static_cast<std::string>(node["position"]) == "kSTELLER")
    {
        position_ = Position::kSTELLER;
    }
    else if (static_cast<std::string>(node["position"]) == "kMITTELBLOCKER")
    {
        position_ = Position::kMITTELBLOCKER;
    }
    else if (static_cast<std::string>(node["position"]) == "kAUSSENANGREIFER")
    {
        position_ = Position::kAUSSENANGREIFER;
    }
    else
    {
        position_ = Position::kUNDEFINED;
    }
    number_of_actions_ = static_cast<int>(node["numberOfActions"]);
}

bool Player::operator==(Player player_to_compare) const
{
    return this->GetName() == player_to_compare.GetName() && this->GetNumber() == player_to_compare.GetNumber();
}
