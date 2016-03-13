#include "opensurf_cmt_wrapper.h"

using namespace cv;

/*
Detect wraps the following OpenSURF (surflib.h) function call:
inline void surfDet(IplImage *img,  image to find Ipoints in 
                    std::vector<Ipoint> &ipts,  reference to vector of Ipoints 
                    int octaves = OCTAVES, number of octaves to calculate 
                    int intervals = INTERVALS,  number of intervals per octave 
                    int init_sample = INIT_SAMPLE,  initial sampling step 
                    float thres = THRES  blob response threshold 
*/
void SURFWrapper::detect(const Mat& image, vector<KeyPoint>& keypoints, const Mat& mask)
{
	IplImage *iplImage = new IplImage(image);
	vector<Ipoint> keypoints_ipoints = vector<Ipoint>();

	surfDet(iplImage, keypoints_ipoints);

	// Now we convert each ipoint in keypoint_ipoints to KeyPoint.
	for each (Ipoint ipoint in keypoints_ipoints)
	{
		KeyPoint keypoint = KeyPoint();

		// TODO we need to figure out which of the KeyPoint fields are actually used,
		//	and make sure those are filled out here.
		keypoint.pt = Point2f(ipoint.x, ipoint.y);
		keypoint.angle = ipoint.orientation;		// TODO may have to shift this here.
		keypoint.octave;
		keypoint.size = ipoint.scale;				// TODO don't think this is right.

		keypoints.push_back(keypoint);
	}
}

/*
Compute wraps the following OpenSURF (surflib.h) function call:
inline void surfDes(IplImage *img,   image to find Ipoints in 
                    std::vector<Ipoint> &ipts,  reference to vector of Ipoints 
                    bool upright = false)  run in rotation invariant mode? 
*/
void SURFWrapper::compute(const Mat& image, vector<KeyPoint>& keypoints, Mat& descriptors)
{
	IplImage *iplImage = new IplImage(image);
	vector<Ipoint> keypoints_ipoints = vector<Ipoint>();

	// Now we convert each Keypoint to an ipoint, the opposite of what we do above.
	for (int i = 0; i < keypoints.size(); i++)
	{
		KeyPoint keypoint = keypoints.at(i);
		Ipoint ipoint = Ipoint();

		ipoint.x = keypoint.pt.x;
		ipoint.y = keypoint.pt.y;
		ipoint.orientation = keypoint.angle;
		ipoint.scale = keypoint.size;

		keypoints_ipoints.push_back(ipoint);
	}


	surfDes(iplImage, keypoints_ipoints);

	// Row i contains the 64 descriptors for keypoint i.
	Mat descriptors_temp = Mat(keypoints.size(), 64, CV_32FC1);	// TODO can we initialize with 0 rows and add with push_back below?

	for (int i = 0; i < keypoints.size(); i++)
	{	
		Ipoint ipoint = keypoints_ipoints.at(i);
		Mat row = Mat(1, 64, CV_32F);
		for (int j = 0; j < 64; j++) row.at<float>(0,j) = ipoint.descriptor[j];
		row.row(0).copyTo(descriptors_temp.row(i));
	}

	descriptors = Mat(descriptors_temp.size(), CV_8UC1);
	descriptors_temp.convertTo(descriptors, CV_8U);
}

void SURFWrapper::detectAndCompute(const Mat& image, vector<KeyPoint>& keypoints, Mat& descriptors, const Mat& mask)
{
	IplImage *iplImage = new IplImage(image);
	vector<Ipoint> keypoints_ipoints = vector<Ipoint>();

	surfDetDes(iplImage, keypoints_ipoints);

	// Add keypoints into the return vector (keypoints)
	for (int i = 0; i < keypoints_ipoints.size(); i++)
	{
		KeyPoint keypoint = KeyPoint();
		Ipoint ipoint = keypoints_ipoints.at(i);

		// Because of how we use the returned vector in CMT.cpp, we only need to return the location.
		keypoint.pt = Point2f(ipoint.x, ipoint.y);
		//keypoint.angle = ipoint.orientation;		// TODO may have to shift this here.
		//keypoint.octave;
		//keypoint.size = ipoint.scale;				// TODO don't think this is right.

		keypoints.push_back(keypoint);
	}
	
	// Put descriptors in the return Mat.
	//	(Row i contains the 64 descriptors for keypoint i.)
	Mat descriptors_temp = Mat(keypoints_ipoints.size(), 64, CV_32FC1);	// TODO can we initialize with 0 rows and add with push_back below?
	for (int i = 0; i < keypoints_ipoints.size(); i++)
	{
		Ipoint ipoint = keypoints_ipoints.at(i);
		Mat row = Mat(1, 64, CV_32F);
		for (int j = 0; j < 64; j++) row.at<float>(0, j) = ipoint.descriptor[j];
		row.row(0).copyTo(descriptors_temp.row(i));
	}

	descriptors = Mat(descriptors_temp.size(), CV_8UC1);
	descriptors_temp.convertTo(descriptors, CV_8U);

}