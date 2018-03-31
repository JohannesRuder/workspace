//
// Created by hannes on 09.03.18.
//

#include <gtest/gtest-message.h>         // for Message
#include <gtest/gtest-test-part.h>       // for TestFactoryImpl, TestPartResult
#include <opencv2/core/hal/interface.h>  // for CV_32S, CV_8U, CV_16S
#include <opencv2/core/mat.hpp>          // for Mat, MatExpr
#include <opencv2/core/mat.inl.hpp>      // for Mat::Mat, Mat::~Mat, MatExpr...
#include "gtest/gtest_pred_impl.h"       // IWYU pragma: keep // for AssertionResult, Test, TEST
// IWYU pragma: no_include <gtest/gtest.h>


#include "../src/utils.h"  // for IsMatEqual

TEST(Utils, IsMatrixEqual_BothMatricesEmpty)
{
    cv::Mat empty_matrix_1{};
    cv::Mat empty_matrix_2{};

    EXPECT_TRUE(IsMatEqual(empty_matrix_1, empty_matrix_2));
}

TEST(Utils, IsMatrixEqual_DifferentDimensions)
{
    cv::Mat arbitrary_matrix_1{2, 4, CV_8U};
    cv::Mat arbitrary_matrix_2{4, 2, CV_8U};

    EXPECT_FALSE(IsMatEqual(arbitrary_matrix_1, arbitrary_matrix_2));
}

TEST(Utils, IsMatrixEqual_DifferentType)
{
    cv::Mat arbitrary_matrix_1{cv::Mat::eye(2, 2, CV_32S)};
    cv::Mat arbitrary_matrix_2{cv::Mat::eye(2, 2, CV_16S)};

    EXPECT_FALSE(IsMatEqual(arbitrary_matrix_1, arbitrary_matrix_2));
}

TEST(Utils, IsMatrixEqual_DifferentElement)
{
    cv::Mat arbitrary_matrix_1{cv::Mat::eye(2, 2, CV_32S)};
    cv::Mat arbitrary_matrix_2{cv::Mat::eye(2, 2, CV_32S)};

    arbitrary_matrix_2.at<int>(1, 1) = 2;

    EXPECT_FALSE(IsMatEqual(arbitrary_matrix_1, arbitrary_matrix_2));
}

TEST(Utils, IsMatrixEqual_EqualElements)
{
    cv::Mat arbitrary_matrix_1{cv::Mat::eye(2, 2, CV_32S)};
    cv::Mat arbitrary_matrix_2{cv::Mat::eye(2, 2, CV_32S)};

    EXPECT_TRUE(IsMatEqual(arbitrary_matrix_1, arbitrary_matrix_2));
}
