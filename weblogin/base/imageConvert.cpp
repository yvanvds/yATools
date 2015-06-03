/* 
 * File:   imageConvert.cpp
 * Author: yvan
 * 
 * Created on June 3, 2015, 4:25 PM
 */

#include "imageConvert.h"
#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/jpeg_io.hpp>
#include <boost/gil/extension/io/png_io.hpp>
#include "utils/log.h"

void GetDimensions(const string & s, int & x, int & y) {
  boost::gil::point2<std::ptrdiff_t> dimensions;
  try{
    dimensions = boost::gil::png_read_dimensions(s.c_str());
  } catch(const std::ios_base::failure & f) {
    try {
      y::utils::Log().add(string(f.what()));
      dimensions = boost::gil::jpeg_read_dimensions(s.c_str());
    } catch (const std::ios_base::failure & f) {    
      y::utils::Log().add(string(f.what()));
    }
  }
  x = dimensions.x;
  y = dimensions.y;
}