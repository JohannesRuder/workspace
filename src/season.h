//
// Created by hannes on 18.02.18.
//

#ifndef WORKSPACE_SEASON_H
#define WORKSPACE_SEASON_H

#include <opencv2/core/persistence.hpp>  // for FileStorage (ptr only), File...
#include <string>                        // for string, basic_string
#include <vector>                        // for vector

#include "game.h"                        // for Game

class Season
{
  private:
    std::string name_;
    std::string filename_;
    std::vector<Game> games_;

  public:
    Season();
    Season(const std::string& name, const std::string& filename);

    void SetName(const std::string& name);
    const std::string& GetName();
    void SetFilename(const std::string& filename);
    const std::string& GetFilename();
    const std::vector<Game>& GetGames() const;

    const Game& GetGame(int number);
    void AddGame(Game game);

    void Write(cv::FileStorage& file_storage) const;
    void Read(const cv::FileNode& node);
};

inline void write(cv::FileStorage& file_storage, const std::string&, const Season& x)
{
    x.Write(file_storage);
}

inline void read(const cv::FileNode& node, Season& x, const Season& default_value = Season())
{
    if (node.empty())
        x = default_value;
    else
        x.Read(node);
}

#endif  // WORKSPACE_SEASON_H
