#ifndef RECOGNITIONENGINE_H
#define RECOGNITIONENGINE_H
#include "imgobj.h"
#include "objectdispatcher.h"
#include "opencv2/imgcodecs.hpp"
#include <functional>
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>

namespace ce {

class RecognitionEngine
{
protected:
	cv::Ptr<ObjectDispatcher> _dispatcher;
	std::string				  _result;
	std::string				  _img_path = "/tmp/img.jpg";
	
protected:
	std::string runCmd(const char* cmd);
	
public:
	RecognitionEngine();
	void		recognise(P_ImgObj &img);
	void		setDispatcher(cv::Ptr<ObjectDispatcher> dispatcher);
	std::string getRecognitionResult();
};

} // namespace ce

#endif // RECOGNITIONENGINE_H
