#ifndef CE_DISPATCHER_H
#define CE_DISPATCHER_H
#include "imgobj.h"
#include "opencv2/core.hpp"
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/vector.hpp>
BOOST_SERIALIZATION_SPLIT_FREE(::cv::Mat)

namespace ce {

// dispatcher interface
class Dispatcher
{
public:
	virtual void dispatchObject(ce::ImgObj obj) = 0;
};

} // namespace cybeye

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
#endif // CE_DISPATCHER_H
