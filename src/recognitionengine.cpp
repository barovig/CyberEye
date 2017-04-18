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
		cv::imwrite(_img_path, img->getImgData());
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

std::string runCmd(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (!std::feof(pipe)) {
            if (std::fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}
} // namespace ce
