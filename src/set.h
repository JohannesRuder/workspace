//
// Created by hannes on 15.02.18.
//

#ifndef WORKSPACE_SET_H
#define WORKSPACE_SET_H

#include <vector>
#include <opencv2/core/core.hpp>
#include "rally.h"

class Set
{
  private:
    int homeScore_;
    int guestScore_;
    std::vector<Rally> rallies_;

  public:
    Set();

    int GetHomeScore() const;
    int GetGuestScore() const;
    const std::vector<Rally>& GetRallies() const;

    void IncrementHomeScore();
    void IncrementGuestScore();

    bool operator==(const Set &rhs) const;

    void Write(cv::FileStorage& file_storage) const;
    void Read(const cv::FileNode& node);
};

inline void write(cv::FileStorage& file_storage, const std::string&, const Set& x)
{
    x.Write(file_storage);
}

inline void read(const cv::FileNode& node, Set& x, const Set& default_value = Set())
{
    if (node.empty())
        x = default_value;
    else
        x.Read(node);
}

#endif  // WORKSPACE_SET_H
