#ifndef RECOGNITIONENGINE_H
#define RECOGNITIONENGINE_H
#include "imgobj.h"

namespace ce {

class RecognitionEngine
{
public:
	RecognitionEngine();
	void recognise(ImgObj& img);
};

} // namespace ce

#endif // RECOGNITIONENGINE_H
