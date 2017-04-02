#include "objcollection.h"

namespace ce {

ObjCollection::ObjCollection()
{
	
}

void ObjCollection::ObjCollection::add(ImgObj img)
{
}

void ObjCollection::ObjCollection::remove(int id)
{
}

const std::vector<ce::ImgObj> &ObjCollection::ObjCollection::getImgObjects()
{
	return _images;
}

void ObjCollection::ObjCollection::updateLocation(int id, cv::Point location, cv::Size sz)
{
}

void ObjCollection::ObjCollection::updateLabel(int id, std::string label)
{
}

} // namespace ce
