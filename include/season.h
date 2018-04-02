//
// Created by hannes on 18.02.18.
//

#ifndef SEASON_H_
#define SEASON_H_

#include <string>                        // for string, basic_string
#include <vector>                        // for vector
#include <opencv2/core/persistence.hpp>  // for FileStorage (ptr only), File...

#include "game.h"  // for Game

class Season
{
  private:
    std::string name_;
    std::string filename_;
    std::vector<Game> games_;

  public:
    Season() = default;
    Season(const std::string& name, const std::string& filename);

    void SetName(const std::string& name);
    const std::string& GetName();
    void SetFilename(const std::string& filename);
    const std::string& GetFilename();
    const std::vector<Game>& GetGames() const;

    Game & GetGame(int number);
    void AddGame(Game game);

    void Write(cv::FileStorage& file_storage) const;
    void Read(const cv::FileNode& node);
};

inline void write(cv::FileStorage& file_storage, const std::string&, const Season& season)
{
    season.Write(file_storage);
}

inline void read(const cv::FileNode& node, Season& season, const Season& default_value = Season())
{
    if (node.empty())
    {
        season = default_value;
    }
    else
    {
        season.Read(node);
    }
}

#endif  // SEASON_H_
