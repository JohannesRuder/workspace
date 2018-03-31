//
// Created by hannes on 18.02.18.
//

#include "season.h"

#include <opencv2/core/cvstd.inl.hpp>  // for operator<<, FileNode::operator...

Season::Season() : name_{""}, filename_{""}, games_{} {}

Season::Season(const std::string& name, const std::string& filename) : name_{name}, filename_{filename} {}

void Season::SetName(const std::string& name)
{
    name_ = name;
}

const std::string& Season::GetName()
{
    return name_;
}

void Season::SetFilename(const std::string& filename)
{
    filename_ = filename;
}

const std::string& Season::GetFilename()
{
    return filename_;
}

const Game& Season::GetGame(int number)
{
    return games_[number];
}

void Season::AddGame(Game game)
{
    games_.push_back(game);
}

void Season::Write(cv::FileStorage& file_storage) const
{
    file_storage << "{"
                 << "name" << name_ << "filename" << filename_ << "games" << games_ << "}";
}

void Season::Read(const cv::FileNode& node)
{
    name_ = static_cast<std::string>(node["name"]);
    filename_ = static_cast<std::string>(node["filename"]);

    auto file_node = node["games"];
    for (auto&& iterator : file_node)
    {
        Game game;
        iterator >> game;
        games_.push_back(game);
    }
}

const std::vector<Game>& Season::GetGames() const
{
    return games_;
}
