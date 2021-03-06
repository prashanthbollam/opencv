// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html.
//
// Copyright (C) 2017, Intel Corporation, all rights reserved.
// Third party copyrights are property of their respective owners.

#include "test_precomp.hpp"

namespace opencv_test { namespace {

TEST(blobFromImage_4ch, Regression)
{
    Mat ch[4];
    for(int i = 0; i < 4; i++)
        ch[i] = Mat::ones(10, 10, CV_8U)*i;

    Mat img;
    merge(ch, 4, img);
    Mat blob = dnn::blobFromImage(img, 1., Size(), Scalar(), false, false);

    for(int i = 0; i < 4; i++)
    {
        ch[i] = Mat(img.rows, img.cols, CV_32F, blob.ptr(0, i));
        ASSERT_DOUBLE_EQ(cvtest::norm(ch[i], cv::NORM_INF), i);
    }
}

TEST(blobFromImage, allocated)
{
    int size[] = {1, 3, 4, 5};
    Mat img(size[2], size[3], CV_32FC(size[1]));
    Mat blob(4, size, CV_32F);
    void* blobData = blob.data;
    dnn::blobFromImage(img, blob, 1.0 / 255, Size(), Scalar(), false, false);
    ASSERT_EQ(blobData, blob.data);
}

}} // namespace
