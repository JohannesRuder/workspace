//
// Created by hannes on 11.02.18.
//

#ifndef WORKSPACE_PLAYER_H
#define WORKSPACE_PLAYER_H

#include <string>                        // for string, basic_string
#include <opencv2/core/persistence.hpp>  // for FileStorage (ptr only), File...

enum class Position
{
    STELLER,
    MITTELBLOCKER,
    AUSSENANGREIFER,
    UNDEFINED
};

class Player
{
  private:
    std::string name_;
    int number_;
    Position position_;
    int number_of_actions_;

  public:
    Player();
    Player(const std::string& name, int number, Position position);
    const std::string& GetName() const;
    const int& GetNumber() const;
    const Position& GetPosition() const;
    const int& GetNumberOfActions() const;
    void IncrementNumberOfActions();

    void Write(cv::FileStorage& file_storage) const;
    void Read(const cv::FileNode& node);

    bool operator==(Player player_to_compare) const;
};

inline void write(cv::FileStorage& file_storage, const std::string&, const Player& x)
{
    x.Write(file_storage);
}

inline void read(const cv::FileNode& node, Player& x, const Player& default_value = Player())
{
    if (node.empty())
        x = default_value;
    else
        x.Read(node);
}

#endif  // WORKSPACE_PLAYER_H
