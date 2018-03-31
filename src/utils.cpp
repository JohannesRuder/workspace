//
// Created by hannes on 09.03.18.
//

#include "utils.h"

#include <opencv2/core.hpp>          // for compare, countNonZero
#include <opencv2/core/base.hpp>     // for CmpTypes::CMP_NE
#include <opencv2/core/mat.hpp>      // for Mat
#include <opencv2/core/mat.inl.hpp>  // for _InputArray::_InputArray, _Input...

bool IsMatEqual(const cv::Mat& mat_1, const cv::Mat& mat_2)
{
    if (mat_1.empty() && mat_2.empty())
    {
        return true;
    }
    if (mat_1.cols != mat_2.cols || mat_1.rows != mat_2.rows || mat_1.dims != mat_2.dims)
    {
        return false;
    }
    if (mat_1.type() != mat_2.type())
    {
        return false;
    }
    cv::Mat diff{};
    cv::compare(mat_1, mat_2, diff, cv::CMP_NE);
    auto number_of_different_elements = cv::countNonZero(diff);
    return 0 == number_of_different_elements;
}
