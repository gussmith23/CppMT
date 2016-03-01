/***
 * SURFWrapper: a wrapper for OpenSURF to make it "look like" an OpenCV 
 * detector/descriptor.
 * Author: Gus Smith <hfs5022@psu.edu> or <gus@justg.us>
 */

#ifndef OPENSURF_CMT_WRAPPER_H
#define OPENSURF_CMT_WRAPPER_H

#include "surflib.h"
#include <opencv2\opencv.hpp>

class SURFWrapper{
public:
	//SURFWrapper SURFWrapper::create(const string& descriptorExtractorType);
	void SURFWrapper::detect(const cv::Mat& image, cv::vector<cv::KeyPoint>& keypoints, const cv::Mat& mask = cv::Mat());
	void SURFWrapper::compute(const cv::Mat& image, cv::vector<cv::KeyPoint>& keypoints, cv::Mat& descriptors);
};


#endif 