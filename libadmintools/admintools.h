/* 
 * File:   admintools.h
 * Author: yvan
 *
 * Created on May 12, 2014, 6:37 PM
 */

#ifndef ADMINTOOLS_H
#define	ADMINTOOLS_H

#define VERSION "1.2"

#include "defines.h"

//data
#include "data/dateTime.h"
#include "data/database.h"
#include "data/field.h"
#include "data/row.h"
#include "data/adminRights.h"

//ldap
#include "ldap/account.h"
#include "ldap/attributes.h"
#include "ldap/group.h"
#include "ldap/server.h"
#include "ldap/data.h"
#include "ldap/dataset.h"

//samba
#include "samba/samba.h"

//system
#include "system/process.h"
#include "system/workDir.h"
#include "system/file.h"

//utils
#include "utils/config.h"
#include "utils/console.h"
#include "utils/container.h"
#include "utils/convert.h"
#include "utils/log.h"
#include "utils/random.h"
#include "utils/security.h"
#include "utils/watch.h"
#include "utils/string.h"
#include "utils/stringFunctions.h"


//gui
#include "gui/confirmationDialog.h"

//admin
#include "admin/userAdmin.h"

//smartschool
#include "smartschool/smartschool.h"
#endif	/* ADMINTOOLS_H */

