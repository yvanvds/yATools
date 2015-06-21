/* 
 * File:   defines.h
 * Author: yvan
 *
 * Created on May 14, 2015, 9:46 PM
 */

#ifndef DEFINES_H
#define	DEFINES_H

#define DO_PRAGMA(x) _Pragma (#x)
#define TODO(x) DO_PRAGMA(message ("TODO - " #x))

#define TYPE_CN  "cn"
#define TYPE_UID "uid"
#define TYPE_UIDNUMBER "uidNumber"
#define TYPE_WISANAME "wisaName" 

#endif	/* DEFINES_H */

