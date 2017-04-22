#ifndef CE_IMGCOLLECTOR_H
#define CE_IMGCOLLECTOR_H
#include <map>
#include <random>
#include <string>
#include "collector.h"
#include "opencv2/imgproc.hpp"


namespace ce {
/**
 * @brief The ImgCollector class. This class is responsible for producing processed frames 
 * rom the object recognition results intended for final display in a client.
 */
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
	/**
	 * @brief A method that accepts raw frame as an input and draws borders and labels on it.
	 * @param input Reference to raw cv::Mat frame
	 * @param output Reference to output cv::Mat frame
	 */
	void getFrame(const cv::Mat& input, cv::Mat& output);
	/**
	 * @brief This method allows user to set flag whether tracked features should be displayed.
	 * @param print Boolean flag.
	 */
	void setPrintFeatures(bool print);
};

} // namespace ce

#endif // CE_IMGCOLLECTOR_H
