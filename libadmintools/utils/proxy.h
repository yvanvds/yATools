/* 
 * File:   proxy.h
 * Author: yvan
 *
 * Created on February 15, 2015, 10:30 PM
 */

#ifndef PROXY_H
#define	PROXY_H

#include <memory>
#include "../data/database.h"

namespace y {
  namespace utils {
    class proxy {     
    public:
      enum STATUS {
        CLOSED,
        FILTER,
        OPEN,
        INVALID,
      };
      
      proxy();
      
      void getAllRooms(container<y::data::row> & rows);
      
      bool   status(const string & room, STATUS status);
      STATUS status(const string & room               );
      
      proxy & reset();
      void apply();

    private:
      
      const string PROXY = "proxy";
    };

  }
}





#endif	/* PROXY_H */

