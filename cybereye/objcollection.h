#ifndef CE_OBJCOLLECTION_H
#define CE_OBJCOLLECTION_H
#include "collection.h"

namespace ce {

class ObjCollection : public ce::Collection
{
private:
	std::vector<ce::ImgObj> _images;
public:
	ObjCollection();
	
	
	// Collection interface
public:
	void add(ImgObj img);
	void remove(int id);
	const std::vector<ce::ImgObj> &getImgObjects();
	void updateLocation(int id, cv::Point location, cv::Size sz);
	void updateLabel(int id, std::__cxx11::string label);
};

} // namespace ce

#endif // CE_OBJCOLLECTION_H
