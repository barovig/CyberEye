#include "recognitionengine.h"
// DEBUG
#include <iostream>

namespace ce {

RecognitionEngine::RecognitionEngine()
{
	
}

void RecognitionEngine::recognise(P_ImgObj img)
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
		std::string outp = runCmd(_cmd.c_str());
		// DONE. receiver will obtain result through getter
		_result = outp;
	}

}

void RecognitionEngine::setDispatcher(cv::Ptr<ObjectDispatcher> dispatcher)
{
	_dispatcher = dispatcher;
}

void RecognitionEngine::setCmd(std::string cmd)
{
	_cmd = cmd;
}

std::string RecognitionEngine::getRecognitionResult()
{
	return _result;
}

std::string RecognitionEngine::runCmd(const char* cmd) {
    char buffer[CMD_BUFSZ];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (!std::feof(pipe)) {
            if (std::fgets(buffer, CMD_BUFSZ, pipe) != NULL)
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
