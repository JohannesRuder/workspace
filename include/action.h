//
// Created by hannes on 15.02.18.
//

#ifndef ACTION_H_
#define ACTION_H_

#include <string>                        // for string
#include <opencv2/core/persistence.hpp>  // for FileStorage (ptr only), File...
#include <qdatetime.h>                   // for QTime

class Action
{
  private:
    QTime time_;

  public:
    Action();

    explicit Action(const QTime& time);

    const QTime& GetTime() const;
    void SetTime(const QTime& time);

    bool operator==(const Action& rhs) const;

    void Write(cv::FileStorage& file_storage) const;
    void Read(const cv::FileNode& node);
};

inline void write(cv::FileStorage& file_storage, const std::string&, const Action& x)
{
    x.Write(file_storage);
}

inline void read(const cv::FileNode& node, Action& x, const Action& default_value = Action())
{
    if (node.empty())
        x = default_value;
    else
        x.Read(node);
}

#endif  // ACTION_H_
