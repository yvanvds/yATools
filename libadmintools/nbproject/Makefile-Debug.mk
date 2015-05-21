#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/admin/userAdmin.o \
	${OBJECTDIR}/data/database.o \
	${OBJECTDIR}/data/dateTime.o \
	${OBJECTDIR}/data/field.o \
	${OBJECTDIR}/data/row.o \
	${OBJECTDIR}/gui/application.o \
	${OBJECTDIR}/gui/confirmationDialog.o \
	${OBJECTDIR}/gui/stackPage.o \
	${OBJECTDIR}/gui/stackPageManager.o \
	${OBJECTDIR}/ldap/account.o \
	${OBJECTDIR}/ldap/attributes.o \
	${OBJECTDIR}/ldap/data.o \
	${OBJECTDIR}/ldap/dataset.o \
	${OBJECTDIR}/ldap/group.o \
	${OBJECTDIR}/ldap/server.o \
	${OBJECTDIR}/samba/samba.o \
	${OBJECTDIR}/smartschool/smartschool.o \
	${OBJECTDIR}/smartschool/soapC.o \
	${OBJECTDIR}/smartschool/soapV3BindingProxy.o \
	${OBJECTDIR}/system/file.o \
	${OBJECTDIR}/system/process.o \
	${OBJECTDIR}/system/workDir.o \
	${OBJECTDIR}/utils/config.o \
	${OBJECTDIR}/utils/console.o \
	${OBJECTDIR}/utils/container.o \
	${OBJECTDIR}/utils/convert.o \
	${OBJECTDIR}/utils/log.o \
	${OBJECTDIR}/utils/memcontainer.o \
	${OBJECTDIR}/utils/proxy.o \
	${OBJECTDIR}/utils/random.o \
	${OBJECTDIR}/utils/security.o \
	${OBJECTDIR}/utils/sha1.o \
	${OBJECTDIR}/utils/string.o \
	${OBJECTDIR}/utils/stringFunctions.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f10 \
	${TESTDIR}/TestFiles/f11 \
	${TESTDIR}/TestFiles/f8 \
	${TESTDIR}/TestFiles/f9 \
	${TESTDIR}/TestFiles/f5 \
	${TESTDIR}/TestFiles/f4 \
	${TESTDIR}/TestFiles/f13 \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f3 \
	${TESTDIR}/TestFiles/f12 \
	${TESTDIR}/TestFiles/f6

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-Wreturn-type
CXXFLAGS=-Wreturn-type

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/usr/lib/x86_64-linux-gnu -L/usr/lib -lboost_system -lboost_filesystem -lboost_program_options -lcrypt -lmysqlcppconn-static -lmysqlclient -lwthttp -lwt -lldap -llber -lboost_iostreams -lboost_regex -lgsoapssl++ -lboost_locale

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../${CND_CONF}/libsystem.${CND_DLIB_EXT}

../${CND_CONF}/libsystem.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ../${CND_CONF}
	${LINK.cc} -o ../${CND_CONF}/libsystem.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/admin/userAdmin.o: admin/userAdmin.cpp 
	${MKDIR} -p ${OBJECTDIR}/admin
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/admin/userAdmin.o admin/userAdmin.cpp

${OBJECTDIR}/data/database.o: data/database.cpp 
	${MKDIR} -p ${OBJECTDIR}/data
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data/database.o data/database.cpp

${OBJECTDIR}/data/dateTime.o: data/dateTime.cpp 
	${MKDIR} -p ${OBJECTDIR}/data
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data/dateTime.o data/dateTime.cpp

${OBJECTDIR}/data/field.o: data/field.cpp 
	${MKDIR} -p ${OBJECTDIR}/data
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data/field.o data/field.cpp

${OBJECTDIR}/data/row.o: data/row.cpp 
	${MKDIR} -p ${OBJECTDIR}/data
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data/row.o data/row.cpp

${OBJECTDIR}/gui/application.o: gui/application.cpp 
	${MKDIR} -p ${OBJECTDIR}/gui
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gui/application.o gui/application.cpp

${OBJECTDIR}/gui/confirmationDialog.o: gui/confirmationDialog.cpp 
	${MKDIR} -p ${OBJECTDIR}/gui
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gui/confirmationDialog.o gui/confirmationDialog.cpp

${OBJECTDIR}/gui/stackPage.o: gui/stackPage.cpp 
	${MKDIR} -p ${OBJECTDIR}/gui
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gui/stackPage.o gui/stackPage.cpp

${OBJECTDIR}/gui/stackPageManager.o: gui/stackPageManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/gui
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gui/stackPageManager.o gui/stackPageManager.cpp

${OBJECTDIR}/ldap/account.o: ldap/account.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/account.o ldap/account.cpp

${OBJECTDIR}/ldap/attributes.o: ldap/attributes.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/attributes.o ldap/attributes.cpp

${OBJECTDIR}/ldap/data.o: ldap/data.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/data.o ldap/data.cpp

${OBJECTDIR}/ldap/dataset.o: ldap/dataset.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/dataset.o ldap/dataset.cpp

${OBJECTDIR}/ldap/group.o: ldap/group.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/group.o ldap/group.cpp

${OBJECTDIR}/ldap/server.o: ldap/server.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/server.o ldap/server.cpp

${OBJECTDIR}/samba/samba.o: samba/samba.cpp 
	${MKDIR} -p ${OBJECTDIR}/samba
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/samba/samba.o samba/samba.cpp

${OBJECTDIR}/smartschool/smartschool.o: smartschool/smartschool.cpp 
	${MKDIR} -p ${OBJECTDIR}/smartschool
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/smartschool/smartschool.o smartschool/smartschool.cpp

${OBJECTDIR}/smartschool/soapC.o: smartschool/soapC.cpp 
	${MKDIR} -p ${OBJECTDIR}/smartschool
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/smartschool/soapC.o smartschool/soapC.cpp

${OBJECTDIR}/smartschool/soapV3BindingProxy.o: smartschool/soapV3BindingProxy.cpp 
	${MKDIR} -p ${OBJECTDIR}/smartschool
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/smartschool/soapV3BindingProxy.o smartschool/soapV3BindingProxy.cpp

${OBJECTDIR}/system/file.o: system/file.cpp 
	${MKDIR} -p ${OBJECTDIR}/system
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/file.o system/file.cpp

${OBJECTDIR}/system/process.o: system/process.cpp 
	${MKDIR} -p ${OBJECTDIR}/system
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/process.o system/process.cpp

${OBJECTDIR}/system/workDir.o: system/workDir.cpp 
	${MKDIR} -p ${OBJECTDIR}/system
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/workDir.o system/workDir.cpp

${OBJECTDIR}/utils/config.o: utils/config.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/config.o utils/config.cpp

${OBJECTDIR}/utils/console.o: utils/console.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/console.o utils/console.cpp

${OBJECTDIR}/utils/container.o: utils/container.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/container.o utils/container.cpp

${OBJECTDIR}/utils/convert.o: utils/convert.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/convert.o utils/convert.cpp

${OBJECTDIR}/utils/log.o: utils/log.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/log.o utils/log.cpp

${OBJECTDIR}/utils/memcontainer.o: utils/memcontainer.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/memcontainer.o utils/memcontainer.cpp

${OBJECTDIR}/utils/proxy.o: utils/proxy.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/proxy.o utils/proxy.cpp

${OBJECTDIR}/utils/random.o: utils/random.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/random.o utils/random.cpp

${OBJECTDIR}/utils/security.o: utils/security.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/security.o utils/security.cpp

${OBJECTDIR}/utils/sha1.o: utils/sha1.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/sha1.o utils/sha1.cpp

${OBJECTDIR}/utils/string.o: utils/string.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/string.o utils/string.cpp

${OBJECTDIR}/utils/stringFunctions.o: utils/stringFunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/stringFunctions.o utils/stringFunctions.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f10: ${TESTDIR}/data/tests/dataDatabaseTest.o ${TESTDIR}/data/tests/dataDatabaseTestRun.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f10 $^ ${LDLIBSOPTIONS} -lldap -llber ../Debug/libsystem.so -lboost_filesystem -lboost_system -lboost_iostreams `cppunit-config --libs`   

${TESTDIR}/TestFiles/f11: ${TESTDIR}/data/tests/dataDateTimeTest.o ${TESTDIR}/data/tests/dataDateTimeTestRun.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f11 $^ ${LDLIBSOPTIONS} -lldap -llber ../Debug/libsystem.so -lboost_filesystem -lboost_system -lboost_iostreams `cppunit-config --libs`   

${TESTDIR}/TestFiles/f8: ${TESTDIR}/data/tests/dataFieldTest.o ${TESTDIR}/data/tests/dataFieldTestRun.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f8 $^ ${LDLIBSOPTIONS} -lldap -llber ../Debug/libsystem.so -lboost_filesystem -lboost_system -lboost_iostreams `cppunit-config --libs`   

${TESTDIR}/TestFiles/f9: ${TESTDIR}/data/tests/dataRowTest.o ${TESTDIR}/data/tests/dataRowTestRun.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f9 $^ ${LDLIBSOPTIONS} -lldap -llber ../Debug/libsystem.so -lboost_filesystem -lboost_system -lboost_iostreams `cppunit-config --libs`   

${TESTDIR}/TestFiles/f5: ${TESTDIR}/ldap/tests/ldapDataTest.o ${TESTDIR}/ldap/tests/ldapDataTestRun.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f5 $^ ${LDLIBSOPTIONS} -lldap -llber ../Debug/libsystem.so -lboost_filesystem -lboost_system -lboost_iostreams `cppunit-config --libs`   

${TESTDIR}/TestFiles/f4: ${TESTDIR}/ldap/tests/ldapServerTest.o ${TESTDIR}/ldap/tests/ldapServerTestRun.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f4 $^ ${LDLIBSOPTIONS} -lldap -llber ../Debug/libsystem.so -lboost_filesystem -lboost_system -lboost_iostreams `cppunit-config --libs`   

${TESTDIR}/TestFiles/f13: ${TESTDIR}/ldap/tests/ldapGroupTest.o ${TESTDIR}/ldap/tests/ldapGroupTestRun.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f13 $^ ${LDLIBSOPTIONS} -lldap -llber ../Debug/libsystem.so -lboost_filesystem -lboost_system -lboost_iostreams `cppunit-config --libs`   

${TESTDIR}/TestFiles/f1: ${TESTDIR}/ldap/tests/ldpAttributesTest.o ${TESTDIR}/ldap/tests/ldpAttributesTestRun.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} -lldap -llber ../Debug/libsystem.so -lboost_filesystem -lboost_system -lboost_iostreams `cppunit-config --libs`   

${TESTDIR}/TestFiles/f2: ${TESTDIR}/ldap/tests/ldpBaseDataTest.o ${TESTDIR}/ldap/tests/ldpBaseDataTestRun.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} -lldap -llber ../Debug/libsystem.so -lboost_filesystem -lboost_system -lboost_iostreams `cppunit-config --libs`   

${TESTDIR}/TestFiles/f3: ${TESTDIR}/system/tests/sysConfigTest.o ${TESTDIR}/system/tests/sysConfigTestRun.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS} -lldap -llber ../Debug/libsystem.so -lboost_filesystem -lboost_system -lboost_iostreams `cppunit-config --libs`   

${TESTDIR}/TestFiles/f12: ${TESTDIR}/system/tests/systemProcessTest.o ${TESTDIR}/system/tests/systemProcessTestRun.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f12 $^ ${LDLIBSOPTIONS} -lldap -llber ../Debug/libsystem.so -lboost_filesystem -lboost_system -lboost_iostreams `cppunit-config --libs` `cppunit-config --libs`   

${TESTDIR}/TestFiles/f6: ${TESTDIR}/utils/tests/utilsSecurityTest.o ${TESTDIR}/utils/tests/utilsSecurityTestRun.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f6 $^ ${LDLIBSOPTIONS} -lldap -llber ../Debug/libsystem.so -lboost_filesystem -lboost_system -lboost_iostreams `cppunit-config --libs`   


${TESTDIR}/data/tests/dataDatabaseTest.o: data/tests/dataDatabaseTest.cpp 
	${MKDIR} -p ${TESTDIR}/data/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/data/tests/dataDatabaseTest.o data/tests/dataDatabaseTest.cpp


${TESTDIR}/data/tests/dataDatabaseTestRun.o: data/tests/dataDatabaseTestRun.cpp 
	${MKDIR} -p ${TESTDIR}/data/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/data/tests/dataDatabaseTestRun.o data/tests/dataDatabaseTestRun.cpp


${TESTDIR}/data/tests/dataDateTimeTest.o: data/tests/dataDateTimeTest.cpp 
	${MKDIR} -p ${TESTDIR}/data/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/data/tests/dataDateTimeTest.o data/tests/dataDateTimeTest.cpp


${TESTDIR}/data/tests/dataDateTimeTestRun.o: data/tests/dataDateTimeTestRun.cpp 
	${MKDIR} -p ${TESTDIR}/data/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/data/tests/dataDateTimeTestRun.o data/tests/dataDateTimeTestRun.cpp


${TESTDIR}/data/tests/dataFieldTest.o: data/tests/dataFieldTest.cpp 
	${MKDIR} -p ${TESTDIR}/data/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/data/tests/dataFieldTest.o data/tests/dataFieldTest.cpp


${TESTDIR}/data/tests/dataFieldTestRun.o: data/tests/dataFieldTestRun.cpp 
	${MKDIR} -p ${TESTDIR}/data/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/data/tests/dataFieldTestRun.o data/tests/dataFieldTestRun.cpp


${TESTDIR}/data/tests/dataRowTest.o: data/tests/dataRowTest.cpp 
	${MKDIR} -p ${TESTDIR}/data/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/data/tests/dataRowTest.o data/tests/dataRowTest.cpp


${TESTDIR}/data/tests/dataRowTestRun.o: data/tests/dataRowTestRun.cpp 
	${MKDIR} -p ${TESTDIR}/data/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/data/tests/dataRowTestRun.o data/tests/dataRowTestRun.cpp


${TESTDIR}/ldap/tests/ldapDataTest.o: ldap/tests/ldapDataTest.cpp 
	${MKDIR} -p ${TESTDIR}/ldap/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/ldap/tests/ldapDataTest.o ldap/tests/ldapDataTest.cpp


${TESTDIR}/ldap/tests/ldapDataTestRun.o: ldap/tests/ldapDataTestRun.cpp 
	${MKDIR} -p ${TESTDIR}/ldap/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/ldap/tests/ldapDataTestRun.o ldap/tests/ldapDataTestRun.cpp


${TESTDIR}/ldap/tests/ldapServerTest.o: ldap/tests/ldapServerTest.cpp 
	${MKDIR} -p ${TESTDIR}/ldap/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/ldap/tests/ldapServerTest.o ldap/tests/ldapServerTest.cpp


${TESTDIR}/ldap/tests/ldapServerTestRun.o: ldap/tests/ldapServerTestRun.cpp 
	${MKDIR} -p ${TESTDIR}/ldap/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/ldap/tests/ldapServerTestRun.o ldap/tests/ldapServerTestRun.cpp


${TESTDIR}/ldap/tests/ldapGroupTest.o: ldap/tests/ldapGroupTest.cpp 
	${MKDIR} -p ${TESTDIR}/ldap/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/ldap/tests/ldapGroupTest.o ldap/tests/ldapGroupTest.cpp


${TESTDIR}/ldap/tests/ldapGroupTestRun.o: ldap/tests/ldapGroupTestRun.cpp 
	${MKDIR} -p ${TESTDIR}/ldap/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/ldap/tests/ldapGroupTestRun.o ldap/tests/ldapGroupTestRun.cpp


${TESTDIR}/ldap/tests/ldpAttributesTest.o: ldap/tests/ldpAttributesTest.cpp 
	${MKDIR} -p ${TESTDIR}/ldap/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -I. -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/ldap/tests/ldpAttributesTest.o ldap/tests/ldpAttributesTest.cpp


${TESTDIR}/ldap/tests/ldpAttributesTestRun.o: ldap/tests/ldpAttributesTestRun.cpp 
	${MKDIR} -p ${TESTDIR}/ldap/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -I. -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/ldap/tests/ldpAttributesTestRun.o ldap/tests/ldpAttributesTestRun.cpp


${TESTDIR}/ldap/tests/ldpBaseDataTest.o: ldap/tests/ldpBaseDataTest.cpp 
	${MKDIR} -p ${TESTDIR}/ldap/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/ldap/tests/ldpBaseDataTest.o ldap/tests/ldpBaseDataTest.cpp


${TESTDIR}/ldap/tests/ldpBaseDataTestRun.o: ldap/tests/ldpBaseDataTestRun.cpp 
	${MKDIR} -p ${TESTDIR}/ldap/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/ldap/tests/ldpBaseDataTestRun.o ldap/tests/ldpBaseDataTestRun.cpp


${TESTDIR}/system/tests/sysConfigTest.o: system/tests/sysConfigTest.cpp 
	${MKDIR} -p ${TESTDIR}/system/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/system/tests/sysConfigTest.o system/tests/sysConfigTest.cpp


${TESTDIR}/system/tests/sysConfigTestRun.o: system/tests/sysConfigTestRun.cpp 
	${MKDIR} -p ${TESTDIR}/system/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/system/tests/sysConfigTestRun.o system/tests/sysConfigTestRun.cpp


${TESTDIR}/system/tests/systemProcessTest.o: system/tests/systemProcessTest.cpp 
	${MKDIR} -p ${TESTDIR}/system/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/system/tests/systemProcessTest.o system/tests/systemProcessTest.cpp


${TESTDIR}/system/tests/systemProcessTestRun.o: system/tests/systemProcessTestRun.cpp 
	${MKDIR} -p ${TESTDIR}/system/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/system/tests/systemProcessTestRun.o system/tests/systemProcessTestRun.cpp


${TESTDIR}/utils/tests/utilsSecurityTest.o: utils/tests/utilsSecurityTest.cpp 
	${MKDIR} -p ${TESTDIR}/utils/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/utils/tests/utilsSecurityTest.o utils/tests/utilsSecurityTest.cpp


${TESTDIR}/utils/tests/utilsSecurityTestRun.o: utils/tests/utilsSecurityTestRun.cpp 
	${MKDIR} -p ${TESTDIR}/utils/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/utils/tests/utilsSecurityTestRun.o utils/tests/utilsSecurityTestRun.cpp


${OBJECTDIR}/admin/userAdmin_nomain.o: ${OBJECTDIR}/admin/userAdmin.o admin/userAdmin.cpp 
	${MKDIR} -p ${OBJECTDIR}/admin
	@NMOUTPUT=`${NM} ${OBJECTDIR}/admin/userAdmin.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/admin/userAdmin_nomain.o admin/userAdmin.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/admin/userAdmin.o ${OBJECTDIR}/admin/userAdmin_nomain.o;\
	fi

${OBJECTDIR}/data/database_nomain.o: ${OBJECTDIR}/data/database.o data/database.cpp 
	${MKDIR} -p ${OBJECTDIR}/data
	@NMOUTPUT=`${NM} ${OBJECTDIR}/data/database.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data/database_nomain.o data/database.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/data/database.o ${OBJECTDIR}/data/database_nomain.o;\
	fi

${OBJECTDIR}/data/dateTime_nomain.o: ${OBJECTDIR}/data/dateTime.o data/dateTime.cpp 
	${MKDIR} -p ${OBJECTDIR}/data
	@NMOUTPUT=`${NM} ${OBJECTDIR}/data/dateTime.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data/dateTime_nomain.o data/dateTime.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/data/dateTime.o ${OBJECTDIR}/data/dateTime_nomain.o;\
	fi

${OBJECTDIR}/data/field_nomain.o: ${OBJECTDIR}/data/field.o data/field.cpp 
	${MKDIR} -p ${OBJECTDIR}/data
	@NMOUTPUT=`${NM} ${OBJECTDIR}/data/field.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data/field_nomain.o data/field.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/data/field.o ${OBJECTDIR}/data/field_nomain.o;\
	fi

${OBJECTDIR}/data/row_nomain.o: ${OBJECTDIR}/data/row.o data/row.cpp 
	${MKDIR} -p ${OBJECTDIR}/data
	@NMOUTPUT=`${NM} ${OBJECTDIR}/data/row.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data/row_nomain.o data/row.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/data/row.o ${OBJECTDIR}/data/row_nomain.o;\
	fi

${OBJECTDIR}/gui/application_nomain.o: ${OBJECTDIR}/gui/application.o gui/application.cpp 
	${MKDIR} -p ${OBJECTDIR}/gui
	@NMOUTPUT=`${NM} ${OBJECTDIR}/gui/application.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gui/application_nomain.o gui/application.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/gui/application.o ${OBJECTDIR}/gui/application_nomain.o;\
	fi

${OBJECTDIR}/gui/confirmationDialog_nomain.o: ${OBJECTDIR}/gui/confirmationDialog.o gui/confirmationDialog.cpp 
	${MKDIR} -p ${OBJECTDIR}/gui
	@NMOUTPUT=`${NM} ${OBJECTDIR}/gui/confirmationDialog.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gui/confirmationDialog_nomain.o gui/confirmationDialog.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/gui/confirmationDialog.o ${OBJECTDIR}/gui/confirmationDialog_nomain.o;\
	fi

${OBJECTDIR}/gui/stackPage_nomain.o: ${OBJECTDIR}/gui/stackPage.o gui/stackPage.cpp 
	${MKDIR} -p ${OBJECTDIR}/gui
	@NMOUTPUT=`${NM} ${OBJECTDIR}/gui/stackPage.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gui/stackPage_nomain.o gui/stackPage.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/gui/stackPage.o ${OBJECTDIR}/gui/stackPage_nomain.o;\
	fi

${OBJECTDIR}/gui/stackPageManager_nomain.o: ${OBJECTDIR}/gui/stackPageManager.o gui/stackPageManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/gui
	@NMOUTPUT=`${NM} ${OBJECTDIR}/gui/stackPageManager.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gui/stackPageManager_nomain.o gui/stackPageManager.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/gui/stackPageManager.o ${OBJECTDIR}/gui/stackPageManager_nomain.o;\
	fi

${OBJECTDIR}/ldap/account_nomain.o: ${OBJECTDIR}/ldap/account.o ldap/account.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ldap/account.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/account_nomain.o ldap/account.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ldap/account.o ${OBJECTDIR}/ldap/account_nomain.o;\
	fi

${OBJECTDIR}/ldap/attributes_nomain.o: ${OBJECTDIR}/ldap/attributes.o ldap/attributes.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ldap/attributes.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/attributes_nomain.o ldap/attributes.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ldap/attributes.o ${OBJECTDIR}/ldap/attributes_nomain.o;\
	fi

${OBJECTDIR}/ldap/data_nomain.o: ${OBJECTDIR}/ldap/data.o ldap/data.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ldap/data.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/data_nomain.o ldap/data.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ldap/data.o ${OBJECTDIR}/ldap/data_nomain.o;\
	fi

${OBJECTDIR}/ldap/dataset_nomain.o: ${OBJECTDIR}/ldap/dataset.o ldap/dataset.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ldap/dataset.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/dataset_nomain.o ldap/dataset.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ldap/dataset.o ${OBJECTDIR}/ldap/dataset_nomain.o;\
	fi

${OBJECTDIR}/ldap/group_nomain.o: ${OBJECTDIR}/ldap/group.o ldap/group.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ldap/group.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/group_nomain.o ldap/group.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ldap/group.o ${OBJECTDIR}/ldap/group_nomain.o;\
	fi

${OBJECTDIR}/ldap/server_nomain.o: ${OBJECTDIR}/ldap/server.o ldap/server.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ldap/server.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/server_nomain.o ldap/server.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ldap/server.o ${OBJECTDIR}/ldap/server_nomain.o;\
	fi

${OBJECTDIR}/samba/samba_nomain.o: ${OBJECTDIR}/samba/samba.o samba/samba.cpp 
	${MKDIR} -p ${OBJECTDIR}/samba
	@NMOUTPUT=`${NM} ${OBJECTDIR}/samba/samba.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/samba/samba_nomain.o samba/samba.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/samba/samba.o ${OBJECTDIR}/samba/samba_nomain.o;\
	fi

${OBJECTDIR}/smartschool/smartschool_nomain.o: ${OBJECTDIR}/smartschool/smartschool.o smartschool/smartschool.cpp 
	${MKDIR} -p ${OBJECTDIR}/smartschool
	@NMOUTPUT=`${NM} ${OBJECTDIR}/smartschool/smartschool.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/smartschool/smartschool_nomain.o smartschool/smartschool.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/smartschool/smartschool.o ${OBJECTDIR}/smartschool/smartschool_nomain.o;\
	fi

${OBJECTDIR}/smartschool/soapC_nomain.o: ${OBJECTDIR}/smartschool/soapC.o smartschool/soapC.cpp 
	${MKDIR} -p ${OBJECTDIR}/smartschool
	@NMOUTPUT=`${NM} ${OBJECTDIR}/smartschool/soapC.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/smartschool/soapC_nomain.o smartschool/soapC.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/smartschool/soapC.o ${OBJECTDIR}/smartschool/soapC_nomain.o;\
	fi

${OBJECTDIR}/smartschool/soapV3BindingProxy_nomain.o: ${OBJECTDIR}/smartschool/soapV3BindingProxy.o smartschool/soapV3BindingProxy.cpp 
	${MKDIR} -p ${OBJECTDIR}/smartschool
	@NMOUTPUT=`${NM} ${OBJECTDIR}/smartschool/soapV3BindingProxy.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/smartschool/soapV3BindingProxy_nomain.o smartschool/soapV3BindingProxy.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/smartschool/soapV3BindingProxy.o ${OBJECTDIR}/smartschool/soapV3BindingProxy_nomain.o;\
	fi

${OBJECTDIR}/system/file_nomain.o: ${OBJECTDIR}/system/file.o system/file.cpp 
	${MKDIR} -p ${OBJECTDIR}/system
	@NMOUTPUT=`${NM} ${OBJECTDIR}/system/file.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/file_nomain.o system/file.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/system/file.o ${OBJECTDIR}/system/file_nomain.o;\
	fi

${OBJECTDIR}/system/process_nomain.o: ${OBJECTDIR}/system/process.o system/process.cpp 
	${MKDIR} -p ${OBJECTDIR}/system
	@NMOUTPUT=`${NM} ${OBJECTDIR}/system/process.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/process_nomain.o system/process.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/system/process.o ${OBJECTDIR}/system/process_nomain.o;\
	fi

${OBJECTDIR}/system/workDir_nomain.o: ${OBJECTDIR}/system/workDir.o system/workDir.cpp 
	${MKDIR} -p ${OBJECTDIR}/system
	@NMOUTPUT=`${NM} ${OBJECTDIR}/system/workDir.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/workDir_nomain.o system/workDir.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/system/workDir.o ${OBJECTDIR}/system/workDir_nomain.o;\
	fi

${OBJECTDIR}/utils/config_nomain.o: ${OBJECTDIR}/utils/config.o utils/config.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	@NMOUTPUT=`${NM} ${OBJECTDIR}/utils/config.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/config_nomain.o utils/config.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/utils/config.o ${OBJECTDIR}/utils/config_nomain.o;\
	fi

${OBJECTDIR}/utils/console_nomain.o: ${OBJECTDIR}/utils/console.o utils/console.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	@NMOUTPUT=`${NM} ${OBJECTDIR}/utils/console.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/console_nomain.o utils/console.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/utils/console.o ${OBJECTDIR}/utils/console_nomain.o;\
	fi

${OBJECTDIR}/utils/container_nomain.o: ${OBJECTDIR}/utils/container.o utils/container.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	@NMOUTPUT=`${NM} ${OBJECTDIR}/utils/container.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/container_nomain.o utils/container.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/utils/container.o ${OBJECTDIR}/utils/container_nomain.o;\
	fi

${OBJECTDIR}/utils/convert_nomain.o: ${OBJECTDIR}/utils/convert.o utils/convert.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	@NMOUTPUT=`${NM} ${OBJECTDIR}/utils/convert.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/convert_nomain.o utils/convert.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/utils/convert.o ${OBJECTDIR}/utils/convert_nomain.o;\
	fi

${OBJECTDIR}/utils/log_nomain.o: ${OBJECTDIR}/utils/log.o utils/log.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	@NMOUTPUT=`${NM} ${OBJECTDIR}/utils/log.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/log_nomain.o utils/log.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/utils/log.o ${OBJECTDIR}/utils/log_nomain.o;\
	fi

${OBJECTDIR}/utils/memcontainer_nomain.o: ${OBJECTDIR}/utils/memcontainer.o utils/memcontainer.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	@NMOUTPUT=`${NM} ${OBJECTDIR}/utils/memcontainer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/memcontainer_nomain.o utils/memcontainer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/utils/memcontainer.o ${OBJECTDIR}/utils/memcontainer_nomain.o;\
	fi

${OBJECTDIR}/utils/proxy_nomain.o: ${OBJECTDIR}/utils/proxy.o utils/proxy.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	@NMOUTPUT=`${NM} ${OBJECTDIR}/utils/proxy.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/proxy_nomain.o utils/proxy.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/utils/proxy.o ${OBJECTDIR}/utils/proxy_nomain.o;\
	fi

${OBJECTDIR}/utils/random_nomain.o: ${OBJECTDIR}/utils/random.o utils/random.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	@NMOUTPUT=`${NM} ${OBJECTDIR}/utils/random.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/random_nomain.o utils/random.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/utils/random.o ${OBJECTDIR}/utils/random_nomain.o;\
	fi

${OBJECTDIR}/utils/security_nomain.o: ${OBJECTDIR}/utils/security.o utils/security.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	@NMOUTPUT=`${NM} ${OBJECTDIR}/utils/security.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/security_nomain.o utils/security.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/utils/security.o ${OBJECTDIR}/utils/security_nomain.o;\
	fi

${OBJECTDIR}/utils/sha1_nomain.o: ${OBJECTDIR}/utils/sha1.o utils/sha1.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	@NMOUTPUT=`${NM} ${OBJECTDIR}/utils/sha1.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/sha1_nomain.o utils/sha1.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/utils/sha1.o ${OBJECTDIR}/utils/sha1_nomain.o;\
	fi

${OBJECTDIR}/utils/string_nomain.o: ${OBJECTDIR}/utils/string.o utils/string.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	@NMOUTPUT=`${NM} ${OBJECTDIR}/utils/string.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/string_nomain.o utils/string.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/utils/string.o ${OBJECTDIR}/utils/string_nomain.o;\
	fi

${OBJECTDIR}/utils/stringFunctions_nomain.o: ${OBJECTDIR}/utils/stringFunctions.o utils/stringFunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	@NMOUTPUT=`${NM} ${OBJECTDIR}/utils/stringFunctions.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Wall -DDEBUG -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/stringFunctions_nomain.o utils/stringFunctions.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/utils/stringFunctions.o ${OBJECTDIR}/utils/stringFunctions_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f10 || true; \
	    ${TESTDIR}/TestFiles/f11 || true; \
	    ${TESTDIR}/TestFiles/f8 || true; \
	    ${TESTDIR}/TestFiles/f9 || true; \
	    ${TESTDIR}/TestFiles/f5 || true; \
	    ${TESTDIR}/TestFiles/f4 || true; \
	    ${TESTDIR}/TestFiles/f13 || true; \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f3 || true; \
	    ${TESTDIR}/TestFiles/f12 || true; \
	    ${TESTDIR}/TestFiles/f6 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../${CND_CONF}/libsystem.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
