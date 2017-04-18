#ifndef CE_IMGCOLLECTOR_H
#define CE_IMGCOLLECTOR_H
#include <map>
#include <random>
#include <string>
#include "collector.h"
#include "opencv2/imgproc.hpp"


namespace ce {

class ImgCollector : public ce::Collector
{
private:
	cv::RNG								_rng;
	std::map<int, 
			cv::Ptr<cv::Scalar> >		_colours;
	bool								_print_features = false;
public:
	/**
	 * @brief ImgCollector contructor
	 * @param model Ptr to Collection.
	 */
	ImgCollector(cv::Ptr<ce::Collection> model);
	
	// Collector interface
public:
	void getFrame(const cv::Mat& input, cv::Mat& output);
	void setPrintFeatures(bool print);
};

} // namespace ce

#endif // CE_IMGCOLLECTOR_H
