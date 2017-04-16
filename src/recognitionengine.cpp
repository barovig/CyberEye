#include "recognitionengine.h"
// DEBUG
#include <iostream>

namespace ce {

RecognitionEngine::RecognitionEngine()
{
	
}

void RecognitionEngine::recognise(P_ImgObj &img)
{
	if(_dispatcher != nullptr)	// remote engine
	{
		_dispatcher->dispatchObject(img);	
	}
	else						// local engine
	{
		//DEBUG
		std::cout << "Recognised image local: " << img->getId() << std::endl;
	}

}

void RecognitionEngine::setDispatcher(cv::Ptr<ObjectDispatcher> dispatcher)
{
	_dispatcher = dispatcher;
}

std::string RecognitionEngine::getRecognitionResult()
{
	return _result;
}

} // namespace ce
