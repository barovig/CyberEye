#ifndef CE_COLLECTION_H
#define CE_COLLECTION_H
#include "imgobj.h"
#include <vector>

namespace ce {

/**
 * @brief The Collection class. An interface for centralised collection storing ImgObj-s.
 */
class Collection
{
public:
	/**
	 * @brief Collection constructor.
	 */
	Collection() {}
	/**
	 * @brief ~Collection virtual destructor.
	 */
	virtual ~Collection(){}
	/**
	 * @brief Pure virtual method to add new objects to collection.
	 */
	virtual void add(cv::Ptr<cv::Mat>, cv::Rect ) = 0;
	/**
	 * @brief Pure virtual method to remove an item from collection.
	 */
	virtual void remove(int) = 0;
	/**
	 * @brief Pure virtual method to clear entire collection.
	 */
	virtual void clear() = 0;
	/**
	 * @brief Pure virtual method returning a collection.
	 * @return std::vector of smart pointers to ImgObj-s.
	 */
	virtual std::vector<P_ImgObj> getImgObjects() = 0;
};

} // namespace ce

#endif // CE_COLLECTION_H
