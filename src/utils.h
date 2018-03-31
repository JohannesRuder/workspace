//
// Created by hannes on 07.03.18.
//

#ifndef WORKSPACE_UTILS_H
#define WORKSPACE_UTILS_H

namespace cv {
class Mat;
}  // namespace cv

bool IsMatEqual(const cv::Mat& mat_1, const cv::Mat& mat_2);

#endif // WORKSPACE_UTILS_H
