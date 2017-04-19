#ifndef CE_CYBEREYE_H
#define CE_CYBEREYE_H
#include "coremanager.h"
#include "objcollection.h"
#include "objtracker.h"
#include "imgcollector.h"
#include "bkgsegmentationengine.h"
#include "watershedengine.h"
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
/**
 * @brief The CyberEye class. This class acts as an abstraction for CoreManager. 
 * It is responsible for creating and initialising pointers to individual components and passes messages 
 * from client to CoreManager.
 */
class CyberEye
{
private:
	cv::Ptr<ce::CoreManager>			_manager;
	cv::Ptr<ce::WatershedEngine>		_engine;
	cv::Ptr<ce::ImgCollector>			_collector;
	cv::Ptr<ce::ObjTracker>				_tracker;
	cv::Ptr<ce::ObjectDispatcher>		_dispatcher;
	cv::Ptr<RecognitionEngine>			_recengine;	
	cv::Ptr<ce::ObjCollection>			_model;
	int									_vcap_index;
	
	// connection params
	std::string							_ip;
	int									_port;		
public:
	/**
	 * @brief CyberEye default constructor.
	 */
	CyberEye();
	/**
	 * @brief CyberEye constructor 
	 * @param vcap Specifies integer index of video capturing device to use.
	 */
	CyberEye(int vcap);
	~CyberEye();
	/**
	 * @brief This method creates and initialises pointers to components, uses them to instansiate 
	 * CoreManager object and sets everything up.
	 */
	void initialise();
	/**
	 * @brief Sends relevant messages to CoreManager to start individual threads.
	 */
	void start();
	/**
	 * @brief Stops all threads.
	 */
	void stop();
	/**
	 * @brief Performs image segmentation and sets input for supervised segmentation to mask.
	 * @param mask Input cv::Mat object used in supervised segmentation
	 */
	void segment(cv::Mat mask);
	
	/**
	 * @brief Retrieves processed frame with detected image objects.
	 * @param frame Reference to cv::Mat& where processed frame will be saved.
	 */
	void getFrame(cv::Mat& frame);
	/**
	 * @brief Sets the IP of recognition server.
	 * @param ip std::string with IPv4 address.
	 */
	void setIP(std::string ip);
	/**
	 * @brief Sets the port to use to send data.
	 * @param port Integer value of port.
	 */
	void setPort(int port);
	/**
	 * @brief Clears all detected objects from central collection.
	 */
	void clearModel();
	/**
	 * @brief Debugging method. Returns vector of smart pointers to ImgObj's from the central collection.
	 * @return 
	 */
	const std::vector<P_ImgObj> getImages();
};

} // namespace ce

#endif // CE_CYBEREYE_H
