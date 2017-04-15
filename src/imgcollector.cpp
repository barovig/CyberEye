#include "imgcollector.h"

namespace ce {

ImgCollector::ImgCollector(cv::Ptr<ce::Collection> model) : ce::Collector(model)
{
	
}

void ImgCollector::getFrame(const cv::Mat& input, cv::Mat& output)
{
	input.copyTo(output);
	for(ce::ImgObj& img : _model->getImgObjects())
	{
		int id = img.getId();
		double r  = rand() % 255 + 1;
		double g  = rand() % 255 + 1;
		double b  = rand() % 255 + 1;
		
		cv::Ptr<cv::Scalar> pColour( new cv::Scalar(r,g,b,255));
		
		auto itr = _colours.find(id);
		if( itr != _colours.end())
			pColour = itr->second;
		else
			_colours[id] = pColour;
		
		cv::rectangle(output, img.getBoundingRect(), *pColour, 2);
		
		// print feature points
		if(_print_features)
			for(auto f : img.getFeatures())
				cv::circle(output, f, 2, cv::Scalar(0,0,0) );
		
	}
}

void ImgCollector::setPrintFeatures(bool print)
{
	_print_features = print;
}

} // namespace ce
