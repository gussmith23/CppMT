#include "opensurf_cmt_wrapper.h"


/*
Detect wraps the following OpenSURF (surflib.h) function call:
inline void surfDet(IplImage *img,  image to find Ipoints in 
                    std::vector<Ipoint> &ipts,  reference to vector of Ipoints 
                    int octaves = OCTAVES, number of octaves to calculate 
                    int intervals = INTERVALS,  number of intervals per octave 
                    int init_sample = INIT_SAMPLE,  initial sampling step 
                    float thres = THRES  blob response threshold 
*/
void SURFWrapper::detect(const Mat& image, vector<KeyPoint>& keypoints, const Mat& mask = Mat())
{

}

/*
Compute wraps the following OpenSURF (surflib.h) function call:
inline void surfDes(IplImage *img,   image to find Ipoints in 
                    std::vector<Ipoint> &ipts,  reference to vector of Ipoints 
                    bool upright = false)  run in rotation invariant mode? 
*/
void SURFWrapper::compute(const Mat& image, vector<KeyPoint>& keypoints, Mat& descriptors)
{

}
