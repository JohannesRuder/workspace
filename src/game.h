//
// Created by hannes on 15.02.18.
//

#ifndef WORKSPACE_GAME_H
#define WORKSPACE_GAME_H

#include <string>                        // for string
#include <vector>                        // for vector
#include <opencv2/core/persistence.hpp>  // for FileStorage (ptr only), File...

#include "set.h"    // for Set
#include "team.h"   // for Team
#include "video.h"  // for Video

class Game
{
  private:
    int number_;
    Team home_team_;
    Team guest_team_;
    std::vector<Set> sets_;
    std::vector<Video> videos_;
    std::vector<int> video_frames_;

  public:
    Game();
    Game(int number,
         const Team& home_team,
         const Team& guest_team,
         const std::vector<Video>& videos,
         const std::vector<int>& video_frames);

    void SetNumber(const int& number);
    const int& GetNumber() const;
    void SetHomeTeam(const Team& home_team);
    const Team& GetHomeTeam() const;
    void SetGuestTeam(const Team& guest_team);
    const Team& GetGuestTeam() const;
    void AddSet(const Set& set);
    const std::vector<Set>& GetSets() const;
    void AddVideo(const Video& video);
    const std::vector<Video>& GetVideos() const;
    const std::vector<int>& GetVideoFrames() const;

    bool operator==(const Game& rhs) const;

    void Write(cv::FileStorage& file_storage) const;
    void Read(const cv::FileNode& node);
};

inline void write(cv::FileStorage& file_storage, const std::string&, const Game& x)
{
    x.Write(file_storage);
}

inline void read(const cv::FileNode& node, Game& x, const Game& default_value = Game())
{
    if (node.empty())
        x = default_value;
    else
        x.Read(node);
}

#endif  // WORKSPACE_GAME_H
