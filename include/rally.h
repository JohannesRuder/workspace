//
// Created by hannes on 15.02.18.
//

#ifndef RALLY_H_
#define RALLY_H_

#include <string>                        // for string
#include <vector>                        // for vector
#include <opencv2/core/persistence.hpp>  // for FileStorage (ptr only), File...
#include <qdatetime.h>                   // for QTime

#include "action.h"  // for Action

class Rally
{
  private:
    QTime start_time_;
    std::vector<Action> actions_;

  public:
    Rally() = default;

    explicit Rally(const QTime& start_time);

    const QTime& GetStartTime() const;
    void SetStartTime(const QTime& start_time);

    const std::vector<Action>& GetActions() const;
    void AddAction(const Action& action);

    bool operator==(const Rally& rhs) const;

    void Write(cv::FileStorage& file_storage) const;
    void Read(const cv::FileNode& node);
};

inline void write(cv::FileStorage& file_storage, const std::string&, const Rally& x)
{
    x.Write(file_storage);
}

inline void read(const cv::FileNode& node, Rally& x, const Rally& default_value = Rally())
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

#endif  // RALLY_H_
