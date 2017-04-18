#include "objcollection.h"

namespace ce {

ObjCollection::ObjCollection()
{
	
}

void ObjCollection::ObjCollection::add(cv::Ptr<cv::Mat> data, cv::Rect rec)
{
	_collection_lock.lock();
	for(P_ImgObj& img : _images)
	{
		if(similar(*data, img->getImgData()))
			return;
	}
	_lastId++;
	P_ImgObj imgObj(new ImgObj(*data, _lastId, rec));
	_images.push_back(imgObj);
	_collection_lock.unlock();
}

void ObjCollection::ObjCollection::remove(int id)
{
	_collection_lock.lock();
	auto itr = _images.begin();
	for( ; itr != _images.end(); itr++)
		if((*itr)->getId() == id)
			break;
	_images.erase(itr);
	_collection_lock.unlock();
}

std::vector<P_ImgObj> ObjCollection::ObjCollection::getImgObjects()
{
	// guard releases lock when goes out of scope
	std::lock_guard<std::mutex> guard(_collection_lock);
	return _images;
}

void ObjCollection::ObjCollection::updateLocation(int id, cv::Point location, cv::Size sz)
{
}

void ObjCollection::ObjCollection::updateLabel(int id, std::string label)
{
}

bool ObjCollection::similar(const cv::Mat &I1, const cv::Mat &I2)
{
	return false;
	cv::Mat im1, im2;
	I1.copyTo(im1);
	I2.copyTo(im2);
	
	// histogram-based matching
	float range[] = {0,256};
	const float *ranges[] = {range};
	int histSize = 256;
	int numChannels = 3;
	cv::SparseMat hist1, hist2;
	cv::calcHist(&im1, 1, &numChannels, cv::noArray(), hist1, 1, &histSize, ranges, true, false);
	cv::calcHist(&im2, 1, &numChannels, cv::noArray(), hist2, 1, &histSize, ranges, true, false);
	
	double res = cv::compareHist(hist1, hist2, cv::HISTCMP_CORREL);
	
	return res > 0.75; 
}

void ObjCollection::clear()
{
	// prevent race condition
	_collection_lock.lock();
	_images.clear();
	_collection_lock.unlock();
}

} // namespace ce


