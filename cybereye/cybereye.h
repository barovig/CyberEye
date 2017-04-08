#ifndef CE_CYBEREYE_H
#define CE_CYBEREYE_H
#include "coremanager.h"
#include "objcollection.h"
#include "objtracker.h"
#include "imgcollector.h"
#include "bkgsegmentationengine.h"
#include "opencv2/imgproc.hpp"

/*! \mainpage CyberEye Documentation
 *
 * \section intro_sec Installation
 *
 * To install CyberEye use CMake to generate makefiles
 *		
 *		cmake ~/CyberEye
 * 
 * And then compile and install with
 * 
 *		make -j4
 *		make install
 * 
 * \section custom_opencv Customising installation
 * To use OpenCV different from the one installed locally, 
 * set CMAKE_PREFIX_PATH to point to the directory containing OpenCV*.cmake files e.g.
 *   
 *		cmake -DCMAKE_PREFIX_PATH=/home/username/root/ ~/CyberEye
 *
 * To install CyberEye to location different to /usr/local,set CMAKE_INSTALL_PREFIX to install directory of choice e.g.
 *
 *		cmake -DCMAKE_INSTALL_PREFIX=/home/username/root/ ~/CyberEye
 *
 */

namespace ce {

class CyberEye
{
private:
	cv::Ptr<ce::CoreManager>			_manager;
	cv::Ptr<ce::BkgSegmentationEngine>	_engine;
	cv::Ptr<ce::ImgCollector>			_collector;
	cv::Ptr<ce::ObjTracker>				_tracker;
	cv::Ptr<ce::ObjCollection>			_model;
	int									_vcap_index;
public:
	CyberEye();
	CyberEye(int vcap);
	~CyberEye();
	void initialise();
	void start();
	void stop();
	// pass frame as ouptut arg
	void getFrame(cv::Mat& frame);
	
	// debugging methods
	cv::Mat getMask();
	const std::vector<ce::ImgObj>& getImages();
};

} // namespace ce

#endif // CE_CYBEREYE_H
