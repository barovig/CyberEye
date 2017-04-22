#ifndef BACKGROUNDSUBTRACTORTH_H
#define BACKGROUNDSUBTRACTORTH_H
#include "opencv2/opencv.hpp"
#include <vector>

/**
 * @brief The BackgroundSubtractorTH class. This class performs threshold-based
 * background segmentation. UNSTABLE!
 */
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
	
	bool _modelCreated = false;
	void setHighThreshold( float scale );
	void setLowThreshold( float scale );	
	void AllocateImages( const cv::InputArray& I );
	void accumulateBackground( const cv::Mat& I );
	void createModelsfromStats();
	void backgroundDiff(const cv::Mat &I, cv::Mat &Imask);
	void clear();
	
	
public:
	/**
	 * @brief BackgroundSubtractorTH constructor.
	 */
	BackgroundSubtractorTH();
	
	// BackgroundSubtractor interface
public:
	/**
	 * @brief OpenCV interface realisation. Applies background segmentation to frame and output foreground mask.
	 * @param image 
	 * @param fgmask
	 * @param learningRate
	 */
	void apply(cv::InputArray image, cv::OutputArray fgmask, double learningRate = 0);
	/**
	 * @brief OpenCV interface realisation. Returns background image as OutputArray.
	 * @param backgroundImage
	 */
	void getBackgroundImage(cv::OutputArray backgroundImage) const;
};

#endif // BACKGROUNDSUBTRACTORTH_H
