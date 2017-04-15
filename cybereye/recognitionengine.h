#ifndef RECOGNITIONENGINE_H
#define RECOGNITIONENGINE_H
#include "imgobj.h"
#include "objectdispatcher.h"
#include <functional>

namespace ce {

class RecognitionEngine
{
protected:
	cv::Ptr<ObjectDispatcher> _dispatcher;
public:
	RecognitionEngine();
	void recognise(P_ImgObj &img);
	
	void setDispatcher(cv::Ptr<ObjectDispatcher> dispatcher);
};

} // namespace ce

#endif // RECOGNITIONENGINE_H
