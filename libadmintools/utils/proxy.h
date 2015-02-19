/* 
 * File:   proxy.h
 * Author: yvan
 *
 * Created on February 15, 2015, 10:30 PM
 */

#ifndef PROXY_H
#define	PROXY_H

#include <memory>
#include "../data/sqlserver.h"
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
      
      bool   status(const std::wstring & room, STATUS status);
      STATUS status(const std::wstring & room               );
      
      proxy & reset();
      void apply();

    private:
      std::unique_ptr<y::data::server> server;
      std::unique_ptr<y::data::database> db;
      
      const std::wstring PROXY = L"proxy";
    };
    
    proxy & Proxy();
  }
}





#endif	/* PROXY_H */

