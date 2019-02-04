//
// Created by hannes on 15.02.18.
//

#ifndef SET_H_
#define SET_H_

#include <string>                        // for string
#include <vector>                        // for vector
#include <opencv2/core/persistence.hpp>  // for FileStorage (ptr only), File...

#include "rally.h"  // for Rally

class Set
{
  private:
    int home_score_;
    int guest_score_;
    std::vector<Rally> rallies_;

  public:
    int GetHomeScore() const;
    int GetGuestScore() const;
    const std::vector<Rally>& GetRallies() const;

    void IncrementHomeScore();
    void IncrementGuestScore();

    bool operator==(const Set& rhs) const;

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
    {
        x = default_value;
    }
    else
    {
        x.Read(node);
    }
}

#endif  // SET_H_
