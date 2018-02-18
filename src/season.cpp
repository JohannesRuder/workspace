//
// Created by hannes on 18.02.18.
//

#include "season.h"

Season::Season() : name_{""}, filename_{""}, games_{} {}

Season::Season(const QString& name, const QString& filename) : name_{name}, filename_{filename} {}

void Season::SetName(const QString& name)
{
    name_ = name;
}

const QString& Season::GetName()
{
    return name_;
}

void Season::SetFilename(const QString& filename)
{
    filename_ = filename;
}

const QString& Season::GetFilename()
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
                 << "name" << name_.toStdString() << "filename" << filename_.toStdString() << "games" << games_ << "}";
}

void Season::Read(const cv::FileNode& node)
{
    name_ = QString::fromStdString(static_cast<std::string>(node["name"]));
    filename_ = QString::fromStdString(static_cast<std::string>(node["filename"]));

    cv::FileNode file_node = node["games"];
    for (cv::FileNodeIterator iterator = file_node.begin(); iterator != file_node.end(); ++iterator)
    {
        cv::FileNode item_node = *iterator;
        Game game;
        item_node >> game;
        games_.push_back(game);
    }
}

const std::vector<Game>& Season::GetGames() const
{
    return games_;
}
