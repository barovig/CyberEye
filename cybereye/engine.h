#ifndef CE_ENGINE_H
#define CE_ENGINE_H
#include "collection.h"
#include "opencv2/core.hpp"

namespace ce {

class Engine
{
protected:
	cv::Ptr<ce::Collection> _model;
public:
    Engine(ce::Collection* model);
	virtual			~Engine(){}
    virtual void	fillImgObjects(cv::Mat frame) = 0;
	virtual int		getEngineWait() = 0;
};

} // namespace ce

#endif // CE_ENGINE_H
