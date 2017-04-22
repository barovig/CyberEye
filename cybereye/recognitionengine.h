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
	/**
	 * @brief CMD_BUFSZ Maximum size of command (chars).
	 */
	const int				  CMD_BUFSZ = 1024;
	
protected:
	/**
	 * @brief _dispatcher Smart pointer to ObjectDispatcher.
	 */
	cv::Ptr<ObjectDispatcher> _dispatcher;
	/**
	 * @brief _result Stores the result of recognition.
	 */
	std::string				  _result;
	/**
	 * @brief _img_path Path where an image will be saved in filesystem.
	 */
	std::string				  _img_path;
	/**
	 * @brief _cmd Command for third-party recognition framework.
	 */
	std::string               _cmd;
protected:
	/**
	 * @brief Executes third-party framework's command.
	 * @param cmd A command to execute.
	 * @return String with the command's output.
	 */
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
	/**
	 * @brief Sets the path to where temporary image will be saved in file system
	 * @param path Full path where image can be saved.
	 */
	void setImgPath(std::string path);
};

} // namespace ce

#endif // RECOGNITIONENGINE_H
