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
    Engine(cv::Ptr<Collection> model);
	virtual			~Engine(){}
    virtual void	segment(cv::Mat frame) = 0;
	virtual void	supervisedSegment(cv::Mat frame, cv::InputArray input) = 0;
	virtual int		getEngineWait() = 0;
	
};

} // namespace ce

#endif // CE_ENGINE_H
