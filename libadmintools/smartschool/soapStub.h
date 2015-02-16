/* soapStub.h
   Generated by gSOAP 2.8.16 from interface.h

Copyright(C) 2000-2013, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
GPL or Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#ifndef soapStub_H
#define soapStub_H
#include <vector>
#define SOAP_NAMESPACE_OF_ns1	"https://sanctamaria-aarschot.smartschool.be/Webservices/V3"
#include "stdsoap2.h"
#if GSOAP_VERSION != 20816
# error "GSOAP VERSION MISMATCH IN GENERATED CODE: PLEASE REINSTALL PACKAGE"
#endif


/******************************************************************************\
 *                                                                            *
 * Enumerations                                                               *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Types with Custom Serializers                                              *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Classes and Structs                                                        *
 *                                                                            *
\******************************************************************************/


#if 0 /* volatile type: do not declare here, declared elsewhere */

#endif

#ifndef SOAP_TYPE_xsd__anyType
#define SOAP_TYPE_xsd__anyType (8)
/* Primitive xsd:anyType schema type: */
class SOAP_CMAC xsd__anyType
{
public:
	char *__item;
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 8; } /* = unique id SOAP_TYPE_xsd__anyType */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         xsd__anyType() { xsd__anyType::soap_default(NULL); }
	virtual ~xsd__anyType() { }
};
#endif

#ifndef SOAP_TYPE_xsd__int
#define SOAP_TYPE_xsd__int (10)
/* Primitive xsd:int schema type: */
class SOAP_CMAC xsd__int : public xsd__anyType
{
public:
	int __item;
public:
	virtual int soap_type() const { return 10; } /* = unique id SOAP_TYPE_xsd__int */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         xsd__int() { xsd__int::soap_default(NULL); }
	virtual ~xsd__int() { }
};
#endif

#if 0 /* volatile type: do not declare here, declared elsewhere */

#endif

#ifndef SOAP_TYPE_xsd__string
#define SOAP_TYPE_xsd__string (11)
/* Primitive xsd:string schema type: */
class SOAP_CMAC xsd__string : public xsd__anyType
{
public:
	std::string __item;
public:
	virtual int soap_type() const { return 11; } /* = unique id SOAP_TYPE_xsd__string */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         xsd__string() { xsd__string::soap_default(NULL); }
	virtual ~xsd__string() { }
};
#endif

#ifndef SOAP_TYPE_ns1__saveUserResponse
#define SOAP_TYPE_ns1__saveUserResponse (16)
/* ns1:saveUserResponse */
struct ns1__saveUserResponse
{
public:
	xsd__anyType *return_;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:anyType */
public:
	int soap_type() const { return 16; } /* = unique id SOAP_TYPE_ns1__saveUserResponse */
};
#endif

#ifndef SOAP_TYPE_ns1__saveUser
#define SOAP_TYPE_ns1__saveUser (17)
/* ns1:saveUser */
struct ns1__saveUser
{
public:
	std::string accesscode;	/* required element of type xsd:string */
	std::string internnumber;	/* required element of type xsd:string */
	std::string username;	/* required element of type xsd:string */
	std::string passwd1;	/* required element of type xsd:string */
	std::string passwd2;	/* required element of type xsd:string */
	std::string passwd3;	/* required element of type xsd:string */
	std::string name;	/* required element of type xsd:string */
	std::string surname;	/* required element of type xsd:string */
	std::string extranames;	/* required element of type xsd:string */
	std::string initials;	/* required element of type xsd:string */
	std::string sex;	/* required element of type xsd:string */
	std::string birthday;	/* required element of type xsd:string */
	std::string birthplace;	/* required element of type xsd:string */
	std::string birthcountry;	/* required element of type xsd:string */
	std::string address;	/* required element of type xsd:string */
	std::string postalcode;	/* required element of type xsd:string */
	std::string location;	/* required element of type xsd:string */
	std::string country;	/* required element of type xsd:string */
	std::string email;	/* required element of type xsd:string */
	std::string mobilephone;	/* required element of type xsd:string */
	std::string homephone;	/* required element of type xsd:string */
	std::string fax;	/* required element of type xsd:string */
	std::string prn;	/* required element of type xsd:string */
	std::string stamboeknummer;	/* required element of type xsd:string */
	std::string basisrol;	/* required element of type xsd:string */
	std::string untis;	/* required element of type xsd:string */
public:
	int soap_type() const { return 17; } /* = unique id SOAP_TYPE_ns1__saveUser */
};
#endif

#ifndef SOAP_TYPE_ns1__saveClassResponse
#define SOAP_TYPE_ns1__saveClassResponse (19)
/* ns1:saveClassResponse */
struct ns1__saveClassResponse
{
public:
	xsd__anyType *return_;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:anyType */
public:
	int soap_type() const { return 19; } /* = unique id SOAP_TYPE_ns1__saveClassResponse */
};
#endif

#ifndef SOAP_TYPE_ns1__saveClass
#define SOAP_TYPE_ns1__saveClass (20)
/* ns1:saveClass */
struct ns1__saveClass
{
public:
	std::string accesscode;	/* required element of type xsd:string */
	std::string name;	/* required element of type xsd:string */
	std::string desc;	/* required element of type xsd:string */
	std::string code;	/* required element of type xsd:string */
	std::string parent;	/* required element of type xsd:string */
	std::string untis;	/* required element of type xsd:string */
	std::string instituteNumber;	/* required element of type xsd:string */
	std::string adminNumber;	/* required element of type xsd:string */
public:
	int soap_type() const { return 20; } /* = unique id SOAP_TYPE_ns1__saveClass */
};
#endif

#ifndef SOAP_TYPE_ns1__getAllAccountsResponse
#define SOAP_TYPE_ns1__getAllAccountsResponse (22)
/* ns1:getAllAccountsResponse */
struct ns1__getAllAccountsResponse
{
public:
	xsd__anyType *return_;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:anyType */
public:
	int soap_type() const { return 22; } /* = unique id SOAP_TYPE_ns1__getAllAccountsResponse */
};
#endif

#ifndef SOAP_TYPE_ns1__getAllAccounts
#define SOAP_TYPE_ns1__getAllAccounts (23)
/* ns1:getAllAccounts */
struct ns1__getAllAccounts
{
public:
	std::string accesscode;	/* required element of type xsd:string */
	std::string code;	/* required element of type xsd:string */
	std::string recursive;	/* required element of type xsd:string */
public:
	int soap_type() const { return 23; } /* = unique id SOAP_TYPE_ns1__getAllAccounts */
};
#endif

#ifndef SOAP_TYPE_ns1__getAllAccountsExtendedResponse
#define SOAP_TYPE_ns1__getAllAccountsExtendedResponse (25)
/* ns1:getAllAccountsExtendedResponse */
struct ns1__getAllAccountsExtendedResponse
{
public:
	xsd__anyType *return_;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:anyType */
public:
	int soap_type() const { return 25; } /* = unique id SOAP_TYPE_ns1__getAllAccountsExtendedResponse */
};
#endif

#ifndef SOAP_TYPE_ns1__getAllAccountsExtended
#define SOAP_TYPE_ns1__getAllAccountsExtended (26)
/* ns1:getAllAccountsExtended */
struct ns1__getAllAccountsExtended
{
public:
	std::string accesscode;	/* required element of type xsd:string */
	std::string code;	/* required element of type xsd:string */
	std::string recursive;	/* required element of type xsd:string */
public:
	int soap_type() const { return 26; } /* = unique id SOAP_TYPE_ns1__getAllAccountsExtended */
};
#endif

#ifndef SOAP_TYPE_ns1__getAllGroupsAndClassesResponse
#define SOAP_TYPE_ns1__getAllGroupsAndClassesResponse (28)
/* ns1:getAllGroupsAndClassesResponse */
struct ns1__getAllGroupsAndClassesResponse
{
public:
	xsd__anyType *return_;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:anyType */
public:
	int soap_type() const { return 28; } /* = unique id SOAP_TYPE_ns1__getAllGroupsAndClassesResponse */
};
#endif

#ifndef SOAP_TYPE_ns1__getAllGroupsAndClasses
#define SOAP_TYPE_ns1__getAllGroupsAndClasses (29)
/* ns1:getAllGroupsAndClasses */
struct ns1__getAllGroupsAndClasses
{
public:
	std::string accesscode;	/* required element of type xsd:string */
public:
	int soap_type() const { return 29; } /* = unique id SOAP_TYPE_ns1__getAllGroupsAndClasses */
};
#endif

#ifndef SOAP_TYPE_ns1__addCourseResponse
#define SOAP_TYPE_ns1__addCourseResponse (32)
/* ns1:addCourseResponse */
struct ns1__addCourseResponse
{
public:
	std::string return_;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 32; } /* = unique id SOAP_TYPE_ns1__addCourseResponse */
};
#endif

#ifndef SOAP_TYPE_ns1__addCourse
#define SOAP_TYPE_ns1__addCourse (33)
/* ns1:addCourse */
struct ns1__addCourse
{
public:
	std::string accesscode;	/* required element of type xsd:string */
	std::string coursename;	/* required element of type xsd:string */
	std::string coursedesc;	/* required element of type xsd:string */
public:
	int soap_type() const { return 33; } /* = unique id SOAP_TYPE_ns1__addCourse */
};
#endif

#ifndef SOAP_TYPE_ns1__addCourseTeacherResponse
#define SOAP_TYPE_ns1__addCourseTeacherResponse (35)
/* ns1:addCourseTeacherResponse */
struct ns1__addCourseTeacherResponse
{
public:
	xsd__anyType *return_;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:anyType */
public:
	int soap_type() const { return 35; } /* = unique id SOAP_TYPE_ns1__addCourseTeacherResponse */
};
#endif

#ifndef SOAP_TYPE_ns1__addCourseTeacher
#define SOAP_TYPE_ns1__addCourseTeacher (36)
/* ns1:addCourseTeacher */
struct ns1__addCourseTeacher
{
public:
	std::string accesscode;	/* required element of type xsd:string */
	std::string coursename;	/* required element of type xsd:string */
	std::string coursedesc;	/* required element of type xsd:string */
	std::string internnummer;	/* required element of type xsd:string */
	std::string userlist;	/* required element of type xsd:string */
public:
	int soap_type() const { return 36; } /* = unique id SOAP_TYPE_ns1__addCourseTeacher */
};
#endif

#ifndef SOAP_TYPE_ns1__addCourseStudentsResponse
#define SOAP_TYPE_ns1__addCourseStudentsResponse (38)
/* ns1:addCourseStudentsResponse */
struct ns1__addCourseStudentsResponse
{
public:
	xsd__anyType *return_;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:anyType */
public:
	int soap_type() const { return 38; } /* = unique id SOAP_TYPE_ns1__addCourseStudentsResponse */
};
#endif

#ifndef SOAP_TYPE_ns1__addCourseStudents
#define SOAP_TYPE_ns1__addCourseStudents (39)
/* ns1:addCourseStudents */
struct ns1__addCourseStudents
{
public:
	std::string accesscode;	/* required element of type xsd:string */
	std::string coursename;	/* required element of type xsd:string */
	std::string coursedesc;	/* required element of type xsd:string */
	std::string groupIds;	/* required element of type xsd:string */
public:
	int soap_type() const { return 39; } /* = unique id SOAP_TYPE_ns1__addCourseStudents */
};
#endif

#ifndef SOAP_TYPE_ns1__getCoursesResponse
#define SOAP_TYPE_ns1__getCoursesResponse (41)
/* ns1:getCoursesResponse */
struct ns1__getCoursesResponse
{
public:
	std::string return_;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 41; } /* = unique id SOAP_TYPE_ns1__getCoursesResponse */
};
#endif

#ifndef SOAP_TYPE_ns1__getCourses
#define SOAP_TYPE_ns1__getCourses (42)
/* ns1:getCourses */
struct ns1__getCourses
{
public:
	std::string accesscode;	/* required element of type xsd:string */
public:
	int soap_type() const { return 42; } /* = unique id SOAP_TYPE_ns1__getCourses */
};
#endif

#ifndef SOAP_TYPE_ns1__delUserResponse
#define SOAP_TYPE_ns1__delUserResponse (44)
/* ns1:delUserResponse */
struct ns1__delUserResponse
{
public:
	xsd__anyType *return_;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:anyType */
public:
	int soap_type() const { return 44; } /* = unique id SOAP_TYPE_ns1__delUserResponse */
};
#endif

#ifndef SOAP_TYPE_ns1__delUser
#define SOAP_TYPE_ns1__delUser (45)
/* ns1:delUser */
struct ns1__delUser
{
public:
	std::string accesscode;	/* required element of type xsd:string */
	std::string userIdentifier;	/* required element of type xsd:string */
	std::string officialDate;	/* required element of type xsd:string */
public:
	int soap_type() const { return 45; } /* = unique id SOAP_TYPE_ns1__delUser */
};
#endif

#ifndef SOAP_TYPE_ns1__saveUserParameterResponse
#define SOAP_TYPE_ns1__saveUserParameterResponse (47)
/* ns1:saveUserParameterResponse */
struct ns1__saveUserParameterResponse
{
public:
	xsd__anyType *return_;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:anyType */
public:
	int soap_type() const { return 47; } /* = unique id SOAP_TYPE_ns1__saveUserParameterResponse */
};
#endif

#ifndef SOAP_TYPE_ns1__saveUserParameter
#define SOAP_TYPE_ns1__saveUserParameter (48)
/* ns1:saveUserParameter */
struct ns1__saveUserParameter
{
public:
	std::string accesscode;	/* required element of type xsd:string */
	std::string userIdentifier;	/* required element of type xsd:string */
	std::string paramName;	/* required element of type xsd:string */
	std::string paramValue;	/* required element of type xsd:string */
public:
	int soap_type() const { return 48; } /* = unique id SOAP_TYPE_ns1__saveUserParameter */
};
#endif

#ifndef SOAP_TYPE_ns1__getClassListResponse
#define SOAP_TYPE_ns1__getClassListResponse (50)
/* ns1:getClassListResponse */
struct ns1__getClassListResponse
{
public:
	std::string return_;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 50; } /* = unique id SOAP_TYPE_ns1__getClassListResponse */
};
#endif

#ifndef SOAP_TYPE_ns1__getClassList
#define SOAP_TYPE_ns1__getClassList (51)
/* ns1:getClassList */
struct ns1__getClassList
{
public:
	xsd__anyType *accesscode;	/* optional element of type xsd:anyType */
public:
	int soap_type() const { return 51; } /* = unique id SOAP_TYPE_ns1__getClassList */
};
#endif

#ifndef SOAP_TYPE_ns1__saveClassListResponse
#define SOAP_TYPE_ns1__saveClassListResponse (53)
/* ns1:saveClassListResponse */
struct ns1__saveClassListResponse
{
public:
	xsd__anyType *return_;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:anyType */
public:
	int soap_type() const { return 53; } /* = unique id SOAP_TYPE_ns1__saveClassListResponse */
};
#endif

#ifndef SOAP_TYPE_ns1__saveClassList
#define SOAP_TYPE_ns1__saveClassList (54)
/* ns1:saveClassList */
struct ns1__saveClassList
{
public:
	std::string accesscode;	/* required element of type xsd:string */
	std::string serializedList;	/* required element of type xsd:string */
public:
	int soap_type() const { return 54; } /* = unique id SOAP_TYPE_ns1__saveClassList */
};
#endif

#ifndef SOAP_TYPE_ns1__delClassResponse
#define SOAP_TYPE_ns1__delClassResponse (56)
/* ns1:delClassResponse */
struct ns1__delClassResponse
{
public:
	xsd__anyType *return_;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:anyType */
public:
	int soap_type() const { return 56; } /* = unique id SOAP_TYPE_ns1__delClassResponse */
};
#endif

#ifndef SOAP_TYPE_ns1__delClass
#define SOAP_TYPE_ns1__delClass (57)
/* ns1:delClass */
struct ns1__delClass
{
public:
	std::string accesscode;	/* required element of type xsd:string */
	std::string code;	/* required element of type xsd:string */
public:
	int soap_type() const { return 57; } /* = unique id SOAP_TYPE_ns1__delClass */
};
#endif

#ifndef SOAP_TYPE_ns1__saveUserToClassesResponse
#define SOAP_TYPE_ns1__saveUserToClassesResponse (59)
/* ns1:saveUserToClassesResponse */
struct ns1__saveUserToClassesResponse
{
public:
	xsd__anyType *return_;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:anyType */
public:
	int soap_type() const { return 59; } /* = unique id SOAP_TYPE_ns1__saveUserToClassesResponse */
};
#endif

#ifndef SOAP_TYPE_ns1__saveUserToClasses
#define SOAP_TYPE_ns1__saveUserToClasses (60)
/* ns1:saveUserToClasses */
struct ns1__saveUserToClasses
{
public:
	std::string accesscode;	/* required element of type xsd:string */
	std::string userIdentifier;	/* required element of type xsd:string */
	std::string csvList;	/* required element of type xsd:string */
public:
	int soap_type() const { return 60; } /* = unique id SOAP_TYPE_ns1__saveUserToClasses */
};
#endif

#ifndef SOAP_TYPE_ns1__saveUserToClassResponse
#define SOAP_TYPE_ns1__saveUserToClassResponse (62)
/* ns1:saveUserToClassResponse */
struct ns1__saveUserToClassResponse
{
public:
	xsd__anyType *return_;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:anyType */
public:
	int soap_type() const { return 62; } /* = unique id SOAP_TYPE_ns1__saveUserToClassResponse */
};
#endif

#ifndef SOAP_TYPE_ns1__saveUserToClass
#define SOAP_TYPE_ns1__saveUserToClass (63)
/* ns1:saveUserToClass */
struct ns1__saveUserToClass
{
public:
	std::string accesscode;	/* required element of type xsd:string */
	std::string userIdentifier;	/* required element of type xsd:string */
	std::string class_;	/* required element of type xsd:string */
	std::string officialDate;	/* required element of type xsd:string */
public:
	int soap_type() const { return 63; } /* = unique id SOAP_TYPE_ns1__saveUserToClass */
};
#endif

#ifndef SOAP_TYPE_ns1__saveUserToClassesAndGroupsResponse
#define SOAP_TYPE_ns1__saveUserToClassesAndGroupsResponse (65)
/* ns1:saveUserToClassesAndGroupsResponse */
struct ns1__saveUserToClassesAndGroupsResponse
{
public:
	xsd__anyType *return_;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:anyType */
public:
	int soap_type() const { return 65; } /* = unique id SOAP_TYPE_ns1__saveUserToClassesAndGroupsResponse */
};
#endif

#ifndef SOAP_TYPE_ns1__saveUserToClassesAndGroups
#define SOAP_TYPE_ns1__saveUserToClassesAndGroups (66)
/* ns1:saveUserToClassesAndGroups */
struct ns1__saveUserToClassesAndGroups
{
public:
	std::string accesscode;	/* required element of type xsd:string */
	std::string userIdentifier;	/* required element of type xsd:string */
	std::string csvList;	/* required element of type xsd:string */
	int keepOld;	/* required element of type xsd:int */
public:
	int soap_type() const { return 66; } /* = unique id SOAP_TYPE_ns1__saveUserToClassesAndGroups */
};
#endif

#ifndef SOAP_TYPE_ns1__setAccountStatusResponse
#define SOAP_TYPE_ns1__setAccountStatusResponse (68)
/* ns1:setAccountStatusResponse */
struct ns1__setAccountStatusResponse
{
public:
	xsd__anyType *return_;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:anyType */
public:
	int soap_type() const { return 68; } /* = unique id SOAP_TYPE_ns1__setAccountStatusResponse */
};
#endif

#ifndef SOAP_TYPE_ns1__setAccountStatus
#define SOAP_TYPE_ns1__setAccountStatus (69)
/* ns1:setAccountStatus */
struct ns1__setAccountStatus
{
public:
	std::string accesscode;	/* required element of type xsd:string */
	std::string userIdentifier;	/* required element of type xsd:string */
	xsd__anyType *accountStatus;	/* optional element of type xsd:anyType */
public:
	int soap_type() const { return 69; } /* = unique id SOAP_TYPE_ns1__setAccountStatus */
};
#endif

#ifndef SOAP_TYPE_ns1__setAccountPhotoResponse
#define SOAP_TYPE_ns1__setAccountPhotoResponse (71)
/* ns1:setAccountPhotoResponse */
struct ns1__setAccountPhotoResponse
{
public:
	xsd__anyType *return_;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:anyType */
public:
	int soap_type() const { return 71; } /* = unique id SOAP_TYPE_ns1__setAccountPhotoResponse */
};
#endif

#ifndef SOAP_TYPE_ns1__setAccountPhoto
#define SOAP_TYPE_ns1__setAccountPhoto (72)
/* ns1:setAccountPhoto */
struct ns1__setAccountPhoto
{
public:
	std::string accesscode;	/* required element of type xsd:string */
	std::string userIdentifier;	/* required element of type xsd:string */
	std::string photo;	/* required element of type xsd:string */
public:
	int soap_type() const { return 72; } /* = unique id SOAP_TYPE_ns1__setAccountPhoto */
};
#endif

#ifndef SOAP_TYPE_ns1__replaceInumResponse
#define SOAP_TYPE_ns1__replaceInumResponse (74)
/* ns1:replaceInumResponse */
struct ns1__replaceInumResponse
{
public:
	xsd__anyType *return_;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:anyType */
public:
	int soap_type() const { return 74; } /* = unique id SOAP_TYPE_ns1__replaceInumResponse */
};
#endif

#ifndef SOAP_TYPE_ns1__replaceInum
#define SOAP_TYPE_ns1__replaceInum (75)
/* ns1:replaceInum */
struct ns1__replaceInum
{
public:
	std::string accesscode;	/* required element of type xsd:string */
	std::string oldInum;	/* required element of type xsd:string */
	std::string newInum;	/* required element of type xsd:string */
public:
	int soap_type() const { return 75; } /* = unique id SOAP_TYPE_ns1__replaceInum */
};
#endif

#ifndef SOAP_TYPE_ns1__savePasswordResponse
#define SOAP_TYPE_ns1__savePasswordResponse (77)
/* ns1:savePasswordResponse */
struct ns1__savePasswordResponse
{
public:
	xsd__anyType *return_;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:anyType */
public:
	int soap_type() const { return 77; } /* = unique id SOAP_TYPE_ns1__savePasswordResponse */
};
#endif

#ifndef SOAP_TYPE_ns1__savePassword
#define SOAP_TYPE_ns1__savePassword (78)
/* ns1:savePassword */
struct ns1__savePassword
{
public:
	std::string accesscode;	/* required element of type xsd:string */
	std::string userIdentifier;	/* required element of type xsd:string */
	std::string password;	/* required element of type xsd:string */
	int accountType;	/* required element of type xsd:int */
public:
	int soap_type() const { return 78; } /* = unique id SOAP_TYPE_ns1__savePassword */
};
#endif

#ifndef SOAP_TYPE__Struct_1
#define SOAP_TYPE__Struct_1 (80)
/* Sequence of xsd:anyType schema type: */
struct _Struct_1
{
public:
	char **__ptr;
	int __size;
public:
	int soap_type() const { return 80; } /* = unique id SOAP_TYPE__Struct_1 */
};
#endif

#ifndef SOAP_TYPE_ns1__sendMsgResponse
#define SOAP_TYPE_ns1__sendMsgResponse (82)
/* ns1:sendMsgResponse */
struct ns1__sendMsgResponse
{
public:
	xsd__anyType *return_;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:anyType */
public:
	int soap_type() const { return 82; } /* = unique id SOAP_TYPE_ns1__sendMsgResponse */
};
#endif

#ifndef SOAP_TYPE_ns1__sendMsg
#define SOAP_TYPE_ns1__sendMsg (83)
/* ns1:sendMsg */
struct ns1__sendMsg
{
public:
	std::string accesscode;	/* required element of type xsd:string */
	std::string userIdentifier;	/* required element of type xsd:string */
	std::string title;	/* required element of type xsd:string */
	std::string body;	/* required element of type xsd:string */
	std::string senderIdentifier;	/* required element of type xsd:string */
	struct _Struct_1 attachments;	/* required element of type Struct-1 */
	int coaccount;	/* required element of type xsd:int */
public:
	int soap_type() const { return 83; } /* = unique id SOAP_TYPE_ns1__sendMsg */
};
#endif

#ifndef SOAP_TYPE_ns1__getSkoreClassTeacherCourseRelationResponse
#define SOAP_TYPE_ns1__getSkoreClassTeacherCourseRelationResponse (85)
/* ns1:getSkoreClassTeacherCourseRelationResponse */
struct ns1__getSkoreClassTeacherCourseRelationResponse
{
public:
	xsd__anyType *return_;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:anyType */
public:
	int soap_type() const { return 85; } /* = unique id SOAP_TYPE_ns1__getSkoreClassTeacherCourseRelationResponse */
};
#endif

#ifndef SOAP_TYPE_ns1__getSkoreClassTeacherCourseRelation
#define SOAP_TYPE_ns1__getSkoreClassTeacherCourseRelation (86)
/* ns1:getSkoreClassTeacherCourseRelation */
struct ns1__getSkoreClassTeacherCourseRelation
{
public:
	std::string accesscode;	/* required element of type xsd:string */
public:
	int soap_type() const { return 86; } /* = unique id SOAP_TYPE_ns1__getSkoreClassTeacherCourseRelation */
};
#endif

#ifndef SOAP_TYPE_ns1__unregisterStudentResponse
#define SOAP_TYPE_ns1__unregisterStudentResponse (88)
/* ns1:unregisterStudentResponse */
struct ns1__unregisterStudentResponse
{
public:
	xsd__anyType *return_;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:anyType */
public:
	int soap_type() const { return 88; } /* = unique id SOAP_TYPE_ns1__unregisterStudentResponse */
};
#endif

#ifndef SOAP_TYPE_ns1__unregisterStudent
#define SOAP_TYPE_ns1__unregisterStudent (89)
/* ns1:unregisterStudent */
struct ns1__unregisterStudent
{
public:
	std::string accesscode;	/* required element of type xsd:string */
	std::string userIdentifier;	/* required element of type xsd:string */
	std::string officialDate;	/* required element of type xsd:string */
public:
	int soap_type() const { return 89; } /* = unique id SOAP_TYPE_ns1__unregisterStudent */
};
#endif

#ifndef SOAP_TYPE_ns1__getClassTeachersResponse
#define SOAP_TYPE_ns1__getClassTeachersResponse (91)
/* ns1:getClassTeachersResponse */
struct ns1__getClassTeachersResponse
{
public:
	xsd__anyType *return_;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:anyType */
public:
	int soap_type() const { return 91; } /* = unique id SOAP_TYPE_ns1__getClassTeachersResponse */
};
#endif

#ifndef SOAP_TYPE_ns1__getClassTeachers
#define SOAP_TYPE_ns1__getClassTeachers (92)
/* ns1:getClassTeachers */
struct ns1__getClassTeachers
{
public:
	std::string accesscode;	/* required element of type xsd:string */
public:
	int soap_type() const { return 92; } /* = unique id SOAP_TYPE_ns1__getClassTeachers */
};
#endif

#ifndef SOAP_TYPE_ns1__isValidUserCredentialsResponse
#define SOAP_TYPE_ns1__isValidUserCredentialsResponse (94)
/* ns1:isValidUserCredentialsResponse */
struct ns1__isValidUserCredentialsResponse
{
public:
	xsd__anyType *return_;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:anyType */
public:
	int soap_type() const { return 94; } /* = unique id SOAP_TYPE_ns1__isValidUserCredentialsResponse */
};
#endif

#ifndef SOAP_TYPE_ns1__isValidUserCredentials
#define SOAP_TYPE_ns1__isValidUserCredentials (95)
/* ns1:isValidUserCredentials */
struct ns1__isValidUserCredentials
{
public:
	std::string accesscode;	/* required element of type xsd:string */
	std::string username;	/* required element of type xsd:string */
	std::string password;	/* required element of type xsd:string */
public:
	int soap_type() const { return 95; } /* = unique id SOAP_TYPE_ns1__isValidUserCredentials */
};
#endif

#ifndef SOAP_TYPE_ns1__getAbsentsResponse
#define SOAP_TYPE_ns1__getAbsentsResponse (97)
/* ns1:getAbsentsResponse */
struct ns1__getAbsentsResponse
{
public:
	std::string return_;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 97; } /* = unique id SOAP_TYPE_ns1__getAbsentsResponse */
};
#endif

#ifndef SOAP_TYPE_ns1__getAbsents
#define SOAP_TYPE_ns1__getAbsents (98)
/* ns1:getAbsents */
struct ns1__getAbsents
{
public:
	std::string accesscode;	/* required element of type xsd:string */
	std::string userIdentifier;	/* required element of type xsd:string */
	std::string schoolYear;	/* required element of type xsd:string */
public:
	int soap_type() const { return 98; } /* = unique id SOAP_TYPE_ns1__getAbsents */
};
#endif

#ifndef SOAP_TYPE_ns1__returnErrorCodes
#define SOAP_TYPE_ns1__returnErrorCodes (101)
/* ns1:returnErrorCodes */
struct ns1__returnErrorCodes
{
public:
	int soap_type() const { return 101; } /* = unique id SOAP_TYPE_ns1__returnErrorCodes */
#ifdef WITH_NOEMPTYSTRUCT
private:
	char dummy;	/* dummy member to enable compilation */
#endif
};
#endif

#ifndef SOAP_TYPE_ns1__returnCsvErrorCodesResponse
#define SOAP_TYPE_ns1__returnCsvErrorCodesResponse (103)
/* ns1:returnCsvErrorCodesResponse */
struct ns1__returnCsvErrorCodesResponse
{
public:
	std::string return_;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 103; } /* = unique id SOAP_TYPE_ns1__returnCsvErrorCodesResponse */
};
#endif

#ifndef SOAP_TYPE_ns1__returnCsvErrorCodes
#define SOAP_TYPE_ns1__returnCsvErrorCodes (104)
/* ns1:returnCsvErrorCodes */
struct ns1__returnCsvErrorCodes
{
public:
	int soap_type() const { return 104; } /* = unique id SOAP_TYPE_ns1__returnCsvErrorCodes */
#ifdef WITH_NOEMPTYSTRUCT
private:
	char dummy;	/* dummy member to enable compilation */
#endif
};
#endif

#ifndef SOAP_TYPE_ns1__returnJsonErrorCodesResponse
#define SOAP_TYPE_ns1__returnJsonErrorCodesResponse (106)
/* ns1:returnJsonErrorCodesResponse */
struct ns1__returnJsonErrorCodesResponse
{
public:
	std::string return_;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xsd:string */
public:
	int soap_type() const { return 106; } /* = unique id SOAP_TYPE_ns1__returnJsonErrorCodesResponse */
};
#endif

#ifndef SOAP_TYPE_ns1__returnJsonErrorCodes
#define SOAP_TYPE_ns1__returnJsonErrorCodes (107)
/* ns1:returnJsonErrorCodes */
struct ns1__returnJsonErrorCodes
{
public:
	int soap_type() const { return 107; } /* = unique id SOAP_TYPE_ns1__returnJsonErrorCodes */
#ifdef WITH_NOEMPTYSTRUCT
private:
	char dummy;	/* dummy member to enable compilation */
#endif
};
#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Header
#define SOAP_TYPE_SOAP_ENV__Header (108)
/* SOAP Header: */
struct SOAP_ENV__Header
{
public:
	int soap_type() const { return 108; } /* = unique id SOAP_TYPE_SOAP_ENV__Header */
#ifdef WITH_NOEMPTYSTRUCT
private:
	char dummy;	/* dummy member to enable compilation */
#endif
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Code
#define SOAP_TYPE_SOAP_ENV__Code (109)
/* SOAP Fault Code: */
struct SOAP_ENV__Code
{
public:
	char *SOAP_ENV__Value;	/* optional element of type xsd:QName */
	struct SOAP_ENV__Code *SOAP_ENV__Subcode;	/* optional element of type SOAP-ENV:Code */
public:
	int soap_type() const { return 109; } /* = unique id SOAP_TYPE_SOAP_ENV__Code */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (111)
/* SOAP-ENV:Detail */
struct SOAP_ENV__Detail
{
public:
	char *__any;
	int __type;	/* any type of element <fault> (defined below) */
	void *fault;	/* transient */
public:
	int soap_type() const { return 111; } /* = unique id SOAP_TYPE_SOAP_ENV__Detail */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Reason
#define SOAP_TYPE_SOAP_ENV__Reason (113)
/* SOAP-ENV:Reason */
struct SOAP_ENV__Reason
{
public:
	char *SOAP_ENV__Text;	/* optional element of type xsd:string */
public:
	int soap_type() const { return 113; } /* = unique id SOAP_TYPE_SOAP_ENV__Reason */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Fault
#define SOAP_TYPE_SOAP_ENV__Fault (114)
/* SOAP Fault: */
struct SOAP_ENV__Fault
{
public:
	char *faultcode;	/* optional element of type xsd:QName */
	char *faultstring;	/* optional element of type xsd:string */
	char *faultactor;	/* optional element of type xsd:string */
	struct SOAP_ENV__Detail *detail;	/* optional element of type SOAP-ENV:Detail */
	struct SOAP_ENV__Code *SOAP_ENV__Code;	/* optional element of type SOAP-ENV:Code */
	struct SOAP_ENV__Reason *SOAP_ENV__Reason;	/* optional element of type SOAP-ENV:Reason */
	char *SOAP_ENV__Node;	/* optional element of type xsd:string */
	char *SOAP_ENV__Role;	/* optional element of type xsd:string */
	struct SOAP_ENV__Detail *SOAP_ENV__Detail;	/* optional element of type SOAP-ENV:Detail */
public:
	int soap_type() const { return 114; } /* = unique id SOAP_TYPE_SOAP_ENV__Fault */
};
#endif

#endif

/******************************************************************************\
 *                                                                            *
 * Typedefs                                                                   *
 *                                                                            *
\******************************************************************************/

#ifndef SOAP_TYPE__QName
#define SOAP_TYPE__QName (5)
typedef char *_QName;
#endif

#ifndef SOAP_TYPE__XML
#define SOAP_TYPE__XML (6)
typedef char *_XML;
#endif


/******************************************************************************\
 *                                                                            *
 * Externals                                                                  *
 *                                                                            *
\******************************************************************************/


#endif

/* End of soapStub.h */