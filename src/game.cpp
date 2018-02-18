//
// Created by hannes on 15.02.18.
//

#include "game.h"

Game::Game() : number_(0), home_team_(), guest_team_(), sets_(0), videos_(0), video_frames_(0) {}

void Game::SetNumber(const int& number)
{
    number_ = number;
}

const int& Game::GetNumber() const
{
    return number_;
}

void Game::SetHomeTeam(const Team& home_team)
{
    home_team_ = home_team;
}

const Team& Game::GetHomeTeam() const
{
    return home_team_;
}

void Game::SetGuestTeam(const Team& guest_team)
{
    guest_team_ = guest_team;
}

const Team& Game::GetGuestTeam() const
{
    return guest_team_;
}

const std::vector<int>& Game::GetVideoFrames() const
{
    return video_frames_;
}

void Game::Write(cv::FileStorage& file_storage) const
{
    file_storage << "{"
                 << "number" << number_ << "home_team" << home_team_ << "guest_team" << guest_team_ << "sets" << sets_
                 << "videos" << videos_ << "video_frames" << video_frames_ << "}";
}

void Game::Read(const cv::FileNode& node)
{
    number_ = static_cast<int>(node["number"]);
    cv::FileNode file_node = node["home_team"];
    file_node >> home_team_;
    file_node = node["guest_team"];
    file_node >> guest_team_;
    file_node = node["sets"];
    file_node >> sets_;
    file_node = node["videos"];
    file_node >> videos_;
    file_node = node["video_frames"];
    file_node >> video_frames_;
}

Game::Game(int number,
           const Team& home_team,
           const Team& guest_team,
           const std::vector<Video>& videos,
           const std::vector<int>& video_frames)
    : number_(number), home_team_(home_team), guest_team_(guest_team), videos_(videos), video_frames_(video_frames)
{
}

const std::vector<Video>& Game::GetVideos() const
{
    return videos_;
}

void Game::AddVideo(const Video& video)
{
    videos_.push_back(video);
}

const std::vector<Set>& Game::GetSets() const
{
    return sets_;
}

void Game::AddSet(const Set& set)
{
    sets_.push_back(set);
}

bool Game::operator==(const Game& rhs) const
{
    return number_ == rhs.number_ && home_team_ == rhs.home_team_ && guest_team_ == rhs.guest_team_ &&
           sets_ == rhs.sets_ && videos_ == rhs.videos_ && video_frames_ == rhs.video_frames_;
}
