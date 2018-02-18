//
// Created by hannes on 18.02.18.
//

#ifndef WORKSPACE_SEASON_H
#define WORKSPACE_SEASON_H

#include <opencv2/core/core.hpp>
#include "game.h"

#include <QDebug>
#include <QString>

#include <string>
#include <vector>

class Season
{
  private:
    QString name_;
    QString filename_;
    std::vector<Game> games_;

  public:
    explicit Season();
    explicit Season(const QString& name, const QString& filename);

    void SetName(const QString& name);
    const QString& GetName();
    void SetFilename(const QString& filename);
    const QString& GetFilename();
    const std::vector<Game> &GetGames() const;

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
