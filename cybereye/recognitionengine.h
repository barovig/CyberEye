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

/**
 * @brief The RecognitionEngine class. Performs image recognition by calling third-party frameworks.
 * Invokes the specified command at system level, reads the output and updates information in ImgObj.
 */
class RecognitionEngine
{
private:
public:
	const int				  CMD_BUFSZ = 1024;
	
protected:
	cv::Ptr<ObjectDispatcher> _dispatcher;
	std::string				  _result;
	std::string				  _img_path = "/tmp/img.jpg";
	std::string               _cmd;
protected:
	std::string runCmd(const char* cmd);
	
public:
	/**
	 * @brief RecognitionEngine constructor.
	 */
	RecognitionEngine();
	/**
	 * @brief Recognition method. Performs image recognition and stores the result in ImgObj.
	 * @param img A pointer to ImgObj for which recognition is to be obtained.
	 */
	void		recognise(P_ImgObj img);
	/**
	 * @brief Sets the dispatcher component if recognition engine is set up remotely.
	 * @param dispatcher A smart pointer to Dispatcher.
	 */
	void		setDispatcher(cv::Ptr<ObjectDispatcher> dispatcher);
	/**
	 * @brief Sets the command executed in operating system to obtain image recognition result.
	 * @param cmd The command string.
	 */
	void		setCmd(std::string cmd);
	/**
	 * @brief A getter for recognition result
	 * @return A string with the output from recognition framework.
	 */
	std::string getRecognitionResult();
};

} // namespace ce

#endif // RECOGNITIONENGINE_H
