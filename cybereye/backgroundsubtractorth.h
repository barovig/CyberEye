#ifndef BACKGROUNDSUBTRACTORTH_H
#define BACKGROUNDSUBTRACTORTH_H
#include "opencv2/opencv.hpp"
#include <vector>

class BackgroundSubtractorTH : public cv::BackgroundSubtractor
{
private:
	cv::Mat IavgF, IdiffF, IprevF, IhiF, IlowF;
	cv::Mat tmp, tmp2;
	// Float, 1-channel images
	std::vector<cv::Mat> Igray{3};
	std::vector<cv::Mat> Ilow{3};
	std::vector<cv::Mat> Ihi{3};
	// Byte, 1-channel image
	cv::Mat Imaskt;
	// Counts number of images learned for averaging later
	float Icount;
	
	void setHighThreshold( float scale );
	void setLowThreshold( float scale );	
	void AllocateImages( const cv::Mat& I );
	void accumulateBackground( cv::Mat& I );
	void createModelsfromStats();
	void backgroundDiff(cv::Mat& I,cv::Mat& Imask);	
	
	
public:
	BackgroundSubtractorTH();
	
	// BackgroundSubtractor interface
public:
	void apply(cv::InputArray image, cv::OutputArray fgmask, double learningRate = 0);
	void getBackgroundImage(cv::OutputArray backgroundImage) const;
};

#endif // BACKGROUNDSUBTRACTORTH_H
