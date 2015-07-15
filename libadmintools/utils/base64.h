/* 
 * File:   base64.h
 * Author: yvan
 *
 * Created on July 13, 2015, 8:26 PM
 */

#ifndef BASE64_H
#define	BASE64_H

#include <string>

std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);

#endif	/* BASE64_H */

