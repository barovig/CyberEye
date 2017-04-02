#include "engine.h"

namespace ce {

Engine::Engine(cv::Ptr<Collection> model)
{
    _model = model;
}

} // namespace ce
