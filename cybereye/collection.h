#ifndef CE_COLLECTION_H
#define CE_COLLECTION_H
#include "imgobj.h"
#include <vector>

namespace ce {

class Collection
{
private:

protected:

public:
	Collection() {}
	virtual ~Collection(){}
	
	virtual void add(cv::Ptr<cv::Mat> img, cv::Rect ) = 0;
	virtual void remove(int id) = 0;
	virtual void clear() = 0;
	// return a copy of private vector of img objects.
	virtual std::vector<P_ImgObj> getImgObjects() = 0;
	
	// update location only through this method - used by Tracker
	virtual void updateLocation(int id, cv::Point location, cv::Size sz) = 0;
	
	// update label through this method only - used by RecognitionEngine
	virtual void updateLabel(int id, std::string label) = 0;
};

} // namespace ce

#endif // CE_COLLECTION_H
