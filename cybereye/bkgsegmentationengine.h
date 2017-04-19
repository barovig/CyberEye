#ifndef CE_BKGSEGMENTATIONENGINE_H
#define CE_BKGSEGMENTATIONENGINE_H
#include <thread>
#include "opencv2/video.hpp"
#include "opencv2/photo.hpp"
#include "opencv2/imgproc.hpp"
#include "engine.h"

namespace ce {
/**
 * @brief The BkgSegmentationEngine class. This class uses background segmentation 
 * algorithms from OpenCV to perform realtime unsupervised image segmentation. UNSTABLE!
 */
class BkgSegmentationEngine : public Engine
{
public:
	/**
	 * @brief The Method enum for algorithms.
	 */
	enum Method {
		BKG_MOG2, /**< Specifies multiple of gaussian (MOG2) algo. */
		BKG_KNN	  /**< Specifies K-nearest neighbours (KNN) algo. */ 
	};
	
private:
	// Constants
	/**
	 * @brief  Number of iterations of erosion/dilation in connected components analysis.
	 */
	const int	CVCLOSE_ITR = 1;
	/**
	 * @brief  Number of calls to segment() method to skip before performing segmentation.
	 */
	const int	NUM_ITERS_TO_SKIP = 100;	// segmentation will happen every iters*wait = 100*10 = 1s
	
	// Memebers
	/**
	 * @brief  Smart pointer to instance of realisation of BackgroundSubtractor class.
	 */
    cv::Ptr<cv::BackgroundSubtractor>   _subtractor;
	/**
	 * @brief  cv::Mat storing foreground mask, with non-zero pixels denoting foreground objects.
	 */
    cv::Mat                             _mask;
	/**
	 * @brief Learning rate parameter for cv::BackgroundSubtractor. 
	 * Set to -1 to use automatic rate and 0 to stop "learning" background from the call.
	 */
    int								    _update = -1;
	/**
	 * @brief Stores selected subtraction algorithm as Method enum value.
	 */
	Method								_method = BKG_MOG2;
	/**
	 * @brief Integer millisecond value for BkgSegmentationEngine to wait before performing next segmentation.
	 */
	int									_engine_wait_ms = 10;
	
	// gaussian blur default params
	/**
	 * @brief cv::Size storing the size of kernel used in Gaussian Blur procedure. Default set to 5x5 matrix.
	 */
	cv::Size							_kernel_sz = cv::Size(5,5);
	/**
	 * @brief Integer value of Gaussian half-width in x-direction, used to control blur amount (together with kernel).
	 */
	int									_kernel_sigmaX = 5;
	
protected:
	/**
	 * @brief  This method creates an instance of BackgroundSubtractor (one of MOG, MOG2, KNN) based on selected method (using setMethod() );
	 */
    void createSubtractor();
	
public:
	/**
	 * @brief BkgSegmentationEngine constructor.
	 * @param model Smart pointer to ImgObj collection.
	 */
    BkgSegmentationEngine(cv::Ptr<Collection> model);
	/**
	 * @brief BkgSegmentationEngine constructor.
	 * @param model Smart pointer to ImgObj collection.
	 * @param method Method (algorithm) to use for background subtraction.
	 */
	BkgSegmentationEngine(cv::Ptr<Collection> model, Method method);
	
	// Engine interface
	/**
	 * @brief Engine interface realisation, applies selected background segmentation algorithm
	 *  to frame parameter and updates underlying model and _mask.
	 * @param frame cv::Mat to perform background subtraction upon.
	 */
    void segment(cv::Mat frame);
	/**
	 * @brief Engine interface realisation, unused.
	 * @param input unused parameter.
	 */
	void setSupervisedInput(cv::InputArray input);
	/**
	 * @brief Returns time to wait before performing next segmentation procedure.
	 * @return _engine_wait_ms value in milliseconds.
	 */
	int  getEngineWait();
	
	// Public interface
	/**
	 * @brief Returns single-channel binary foreground mask.
	 * @return _mask attribute as cv::CV_8UC1 Mat object.
	 */
	cv::Mat getMask();
	/**
	 * @brief Updates BackgroundSubtractor underlying model and _mask, without component analysis.
	 * @param frame frame cv::Mat to use for update.
	 */
    void updateSubtractor(cv::Mat frame);
	/**
	 * @brief Sets _update value (learning rate) for BackgroundSubtractor algorithm.
	 * @param update Integer value for a flag, -1 for automatic value, 0 for not updating at all.
	 */
	void setUpdateFlag(int update);
	/**
	 * @brief Sets the _method attribute determining background subtraction algorithm to use.
	 * @param m Method enum value for selected algorithm.
	 */
	void setMethod(Method m);
	/**
	 * @brief Sets the number of milliseconds to wait between calls to segmentation engine.
	 * @param ms Integer value of milliseconds to wait.
	 */
	void setEngineWait(int ms);
	/**
	 * @brief Setter for _kernel_sigmaX and _kernel_sz parameters used in Gaussian Blur procedure.
	 * @param sz cv::Size object specifying kernel size.
	 * @param sigmaX Gaussian half-width in x-direction.
	 */
	void setBlurParams(cv::Size sz, int sigmaX);
	
private:
	/**
	 * @brief Internal procedure that cleans up foreground mask. 
	 * It find portions of mask that are likely to belong to same foreground object and returns vector<Rect> 
	 * of bounding rectangles.
	 * @param mask CV_8UC1 Binary foreground mask.
	 * @param bbs std::vector<cv::Rect> of bounding rectangles around foreground objects.
	 * @param perimScale Minimum perimeter for detected contours to be considered foreground object.
	 */
	void findConnectedComponents(
				cv::Mat&				mask,
				std::vector<cv::Rect>&	bbs,
				float					perimScale = 400
			);
	
};

} // namespace ce

#endif // CE_BKGSEGMENTATIONENGINE_H
