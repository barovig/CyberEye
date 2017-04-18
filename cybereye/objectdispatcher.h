#ifndef CE_OBJECTDISPATCHER_H
#define CE_OBJECTDISPATCHER_H
#include "dispatcher.h"
#include "opencv2/core.hpp"
#include <thread>
#include <chrono>
#include <iostream>

namespace ce {

class ObjectDispatcher : public Dispatcher
{
private:
	std::string						_addr;
	int								_port;
	cv::Mat							_data;
	cv::Ptr<ce::ImgObj>				_img;
public:
	static const int HEADER_LENGTH = 8;
	
	// interface realisation
	void dispatchObject(P_ImgObj object);
	
	// thread procedure
	
	void dispatch();
	ObjectDispatcher(std::string address, int port);
};

} // namespace ce

// Mat serialisation
namespace boost{
namespace serialization{
    template<class Archive>
    void save(Archive & ar, const ::cv::Mat& m, const unsigned int)
    {
      size_t elem_sz = m.elemSize();
      size_t type = m.type();
 
      ar & m.cols;
      ar & m.rows;
      ar & elem_sz;
      ar & type;
 
      const size_t data_sz = m.cols * m.rows * elem_sz;
      ar & boost::serialization::make_array(m.ptr(), data_sz);
    }
	template<class Archive>
    void load(Archive & ar, ::cv::Mat& m, const unsigned int)
    {
      int cols, rows;
      size_t elem_sz, type;
 
      ar & cols;
      ar & rows;
      ar & elem_sz;
      ar & type;
 
      m.create(rows, cols, type);
 
      size_t data_size = m.cols * m.rows * elem_sz;
      ar & boost::serialization::make_array(m.ptr(), data_size);	
	}
}
}
#endif // CE_OBJECTDISPATCHER_H
