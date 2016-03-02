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
	for each (KeyPoint keypoint in keypoints)
	{
		Ipoint ipoint = Ipoint();

		ipoint.x = keypoint.pt.x;
		ipoint.y = keypoint.pt.y;
		ipoint.orientation = keypoint.angle;
		ipoint.scale = keypoint.size;

		keypoints_ipoints.push_back(ipoint);
	}


	surfDes(iplImage, keypoints_ipoints);

	// Row i contains the 64 descriptors for keypoint i.
	descriptors = Mat(0, 64, CV_32F);	// TODO can we initialize with 0 rows and add with push_back below?

	for each (Ipoint ipoint in keypoints_ipoints)
	{
		Mat row = Mat(1, 64, CV_32F);
		memcpy(row.data, ipoint.descriptor, 64 * 32);
		descriptors.push_back(row);
	}
}
