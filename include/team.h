//
// Created by hannes on 11.02.18.
//

#ifndef TEAM_H_
#define TEAM_H_

#include <string>                        // for string
#include <vector>                        // for vector
#include <opencv2/core/core.hpp>         // IWYU pragma: keep
#include <opencv2/core/persistence.hpp>  // for FileStorage (ptr only), File...
#include <qstring.h>                     // for QString

#include "player.h"  // for Player

class Team
{
  private:
    QString name_;
    std::vector<Player> players_;

  public:
    explicit Team();
    explicit Team(const QString& name);

    void SetName(const QString& name);
    const QString& GetName() const;

    void AddPlayer(const Player& player);
    const std::vector<Player>& GetPlayers() const;
    const Player& GetPlayer(int player_number) const;

    bool operator==(const Team& rhs) const;

    void Write(cv::FileStorage& file_storage) const;
    void Read(const cv::FileNode& node);
};

inline void write(cv::FileStorage& file_storage, const std::string&, const Team& x)
{
    x.Write(file_storage);
}

inline void read(const cv::FileNode& node, Team& x, const Team& default_value = Team())
{
    if (node.empty())
    {
        x = default_value;
    }
    else
    {
        x.Read(node);
    }
}

#endif  // TEAM_H_
