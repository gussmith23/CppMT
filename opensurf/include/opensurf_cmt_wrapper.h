/***
 * SURFWrapper: a wrapper for OpenSURF to make it "look like" an OpenCV 
 * detector/descriptor.
 * Author: Gus Smith <hfs5022@psu.edu> or <gus@justg.us>
 */

#ifndef OPENSURF_CMT_WRAPPER_H
#define OPENSURF_CMT_WRAPPER_H

#include "surflib.h"
#include <opencv2\opencv.hpp>

using namespace cv;

class SURFWrapper{
public:
	//SURFWrapper SURFWrapper::create(const string& descriptorExtractorType);
	void SURFWrapper::detect(const Mat& image, vector<KeyPoint>& keypoints, const Mat& mask = Mat());
	void SURFWrapper::compute(const Mat& image, vector<KeyPoint>& keypoints, Mat& descriptors);
};


#endif 