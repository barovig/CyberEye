#ifndef CE_ENGINE_H
#define CE_ENGINE_H
#include "model.h"
#include "opencv2/opencv.hpp"

namespace ce {

class Engine
{
protected:
    cv::Ptr<ce::Model> _model;

public:
    Engine(ce::Model* model);
    virtual ~Engine();
    virtual void getImgObjects(cv::Mat frame) = 0;

};

} // namespace ce

#endif // CE_ENGINE_H
