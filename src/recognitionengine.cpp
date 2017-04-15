#include "recognitionengine.h"
// DEBUG
#include <iostream>

namespace ce {

RecognitionEngine::RecognitionEngine()
{
	
}

void RecognitionEngine::recognise(ImgObj &img)
{
	//DEBUG
	std::cout << "Recognised image: " << img.getId() << std::endl;
}

} // namespace ce
