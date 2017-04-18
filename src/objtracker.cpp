#include "objtracker.h"

namespace ce {

ObjTracker::ObjTracker(cv::Ptr<Collection> model) : Tracker(model)
{
}

void ObjTracker::track(const cv::Mat &frame)
{
	// convert frame to grayscale
	cv::Mat grayFrame;
	frame.copyTo(grayFrame);
	cv::cvtColor(grayFrame, grayFrame, cv::COLOR_BGR2GRAY);
	
	// helper objects
	cv::TermCriteria termcrit(cv::TermCriteria::COUNT|cv::TermCriteria::EPS, 20, 0.03);
    cv::Size subPixWinSize(10,10), winSize(31,31);
	
	for(P_ImgObj img : _model->getImgObjects())	// use reference to modify
	{
		std::vector<cv::Point2f> features = img->getFeatures();
		std::vector<cv::Point2f> newFeatures;
		// find features if empty		
		if(features.empty())
		{
			// convert imgData to grayscale
			cv::Mat grayImg;
			cv::cvtColor(img->getImgData(), grayImg, cv::COLOR_BGR2GRAY);
			// find features and clean up corners.
			// NOTE: features are points relative to imgObj's data, not frame
			cv::goodFeaturesToTrack(grayImg, features, _feature_count, _quality_level, _min_distance, cv::noArray());
			cv::cornerSubPix(grayImg, features, subPixWinSize, cv::Size(-1,-1), termcrit);
			
			// translate feature points by top-left corner of rec
			cv::Point2f tl = img->getBoundingRect().tl();
			for(auto& f : features) f+= tl;
			img->setFeatures(features);
		}
		else
		{
			if(_prev_frame.empty())
				grayFrame.copyTo(_prev_frame);
			
			// error and status vectors for each feature point
			std::vector<uchar> status;
			std::vector<float> errors;
			
			// calculate new position of features (with optical flow)
			cv::calcOpticalFlowPyrLK(_prev_frame, grayFrame, features, newFeatures, 
									 status, errors, winSize, _lk_max_level, termcrit,
									 _lk_flags, _lk_eig_thres);
			
			// sanity check - feature is in frame
			cv::Rect frameRec(frame.size(), cv::Point(0,0));
			features.clear();
			for(auto& f : newFeatures)
				if(frameRec.contains(f))
					features.push_back(f);
			
			// update features and locations			
			img->setFeatures(features);
			cv::Rect rec = cv::boundingRect(newFeatures);
			img->setBoundingRect(rec);
		}
	}
	// update previous frame
	cv::swap(grayFrame, _prev_frame);
}

} // namespace ce
