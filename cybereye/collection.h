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
	
	virtual void add(cv::Mat &img, cv::Rect ) = 0;
	virtual void remove(int id) = 0;
	
	// return a const reference to private vector of img objects.
	virtual std::vector<ce::ImgObj>& getImgObjects() = 0;
	
	// update location only through this method - used by Tracker
	virtual void updateLocation(int id, cv::Point location, cv::Size sz) = 0;
	
	// update label through this method only - used by RecognitionEngine
	virtual void updateLabel(int id, std::string label) = 0;
};

} // namespace ce

#endif // CE_COLLECTION_H
