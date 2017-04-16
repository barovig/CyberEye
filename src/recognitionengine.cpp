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
		std::cout << "Recognised image of area " << img->getImgData().size().area() << std::endl;
		
		// write image to file 
		
		// run recognition framework and save output
		
		// DONE. receiver will obtain result through getter
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
