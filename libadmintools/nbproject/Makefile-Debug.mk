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
	${OBJECTDIR}/data/database.o \
	${OBJECTDIR}/data/dateTime.o \
	${OBJECTDIR}/data/field.o \
	${OBJECTDIR}/data/row.o \
	${OBJECTDIR}/data/sqlserver.o \
	${OBJECTDIR}/gui/application.o \
	${OBJECTDIR}/ldap/account.o \
	${OBJECTDIR}/ldap/attributes.o \
	${OBJECTDIR}/ldap/data.o \
	${OBJECTDIR}/ldap/dataset.o \
	${OBJECTDIR}/ldap/editableGroup.o \
	${OBJECTDIR}/ldap/group.o \
	${OBJECTDIR}/ldap/mailGroup.o \
	${OBJECTDIR}/ldap/server.o \
	${OBJECTDIR}/system/process.o \
	${OBJECTDIR}/system/workDir.o \
	${OBJECTDIR}/utils/config.o \
	${OBJECTDIR}/utils/container.o \
	${OBJECTDIR}/utils/convert.o \
	${OBJECTDIR}/utils/log.o \
	${OBJECTDIR}/utils/security.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f10 \
	${TESTDIR}/TestFiles/f11 \
	${TESTDIR}/TestFiles/f8 \
	${TESTDIR}/TestFiles/f9 \
	${TESTDIR}/TestFiles/f7 \
	${TESTDIR}/TestFiles/f5 \
	${TESTDIR}/TestFiles/f4 \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f3 \
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
LDLIBSOPTIONS=-L/usr/lib/x86_64-linux-gnu -L/usr/lib -lboost_system -lboost_filesystem -lboost_program_options -lcrypt -lmysqlcppconn-static -lmysqlclient -lwthttp -lwt -lldap -llber -lboost_iostreams

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../${CND_CONF}/libsystem.${CND_DLIB_EXT}

../${CND_CONF}/libsystem.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ../${CND_CONF}
	${LINK.cc} -o ../${CND_CONF}/libsystem.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/data/database.o: data/database.cpp 
	${MKDIR} -p ${OBJECTDIR}/data
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data/database.o data/database.cpp

${OBJECTDIR}/data/dateTime.o: data/dateTime.cpp 
	${MKDIR} -p ${OBJECTDIR}/data
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data/dateTime.o data/dateTime.cpp

${OBJECTDIR}/data/field.o: data/field.cpp 
	${MKDIR} -p ${OBJECTDIR}/data
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data/field.o data/field.cpp

${OBJECTDIR}/data/row.o: data/row.cpp 
	${MKDIR} -p ${OBJECTDIR}/data
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data/row.o data/row.cpp

${OBJECTDIR}/data/sqlserver.o: data/sqlserver.cpp 
	${MKDIR} -p ${OBJECTDIR}/data
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data/sqlserver.o data/sqlserver.cpp

${OBJECTDIR}/gui/application.o: gui/application.cpp 
	${MKDIR} -p ${OBJECTDIR}/gui
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gui/application.o gui/application.cpp

${OBJECTDIR}/ldap/account.o: ldap/account.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/account.o ldap/account.cpp

${OBJECTDIR}/ldap/attributes.o: ldap/attributes.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/attributes.o ldap/attributes.cpp

${OBJECTDIR}/ldap/data.o: ldap/data.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/data.o ldap/data.cpp

${OBJECTDIR}/ldap/dataset.o: ldap/dataset.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/dataset.o ldap/dataset.cpp

${OBJECTDIR}/ldap/editableGroup.o: ldap/editableGroup.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/editableGroup.o ldap/editableGroup.cpp

${OBJECTDIR}/ldap/group.o: ldap/group.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/group.o ldap/group.cpp

${OBJECTDIR}/ldap/mailGroup.o: ldap/mailGroup.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/mailGroup.o ldap/mailGroup.cpp

${OBJECTDIR}/ldap/server.o: ldap/server.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/server.o ldap/server.cpp

${OBJECTDIR}/system/process.o: system/process.cpp 
	${MKDIR} -p ${OBJECTDIR}/system
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/process.o system/process.cpp

${OBJECTDIR}/system/workDir.o: system/workDir.cpp 
	${MKDIR} -p ${OBJECTDIR}/system
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/workDir.o system/workDir.cpp

${OBJECTDIR}/utils/config.o: utils/config.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/config.o utils/config.cpp

${OBJECTDIR}/utils/container.o: utils/container.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/container.o utils/container.cpp

${OBJECTDIR}/utils/convert.o: utils/convert.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/convert.o utils/convert.cpp

${OBJECTDIR}/utils/log.o: utils/log.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/log.o utils/log.cpp

${OBJECTDIR}/utils/security.o: utils/security.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/security.o utils/security.cpp

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

${TESTDIR}/TestFiles/f7: ${TESTDIR}/data/tests/dataServerTest.o ${TESTDIR}/data/tests/dataServerTestRun.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f7 $^ ${LDLIBSOPTIONS} -lldap -llber ../Debug/libsystem.so -lboost_filesystem -lboost_system -lboost_iostreams `cppunit-config --libs`   

${TESTDIR}/TestFiles/f5: ${TESTDIR}/ldap/tests/ldapDataTest.o ${TESTDIR}/ldap/tests/ldapDataTestRun.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f5 $^ ${LDLIBSOPTIONS} -lldap -llber ../Debug/libsystem.so -lboost_filesystem -lboost_system -lboost_iostreams `cppunit-config --libs`   

${TESTDIR}/TestFiles/f4: ${TESTDIR}/ldap/tests/ldapServerTest.o ${TESTDIR}/ldap/tests/ldapServerTestRun.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f4 $^ ${LDLIBSOPTIONS} -lldap -llber ../Debug/libsystem.so -lboost_filesystem -lboost_system -lboost_iostreams `cppunit-config --libs`   

${TESTDIR}/TestFiles/f1: ${TESTDIR}/ldap/tests/ldpAttributesTest.o ${TESTDIR}/ldap/tests/ldpAttributesTestRun.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} -lldap -llber ../Debug/libsystem.so -lboost_filesystem -lboost_system -lboost_iostreams `cppunit-config --libs`   

${TESTDIR}/TestFiles/f2: ${TESTDIR}/ldap/tests/ldpBaseDataTest.o ${TESTDIR}/ldap/tests/ldpBaseDataTestRun.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} -lldap -llber ../Debug/libsystem.so -lboost_filesystem -lboost_system -lboost_iostreams `cppunit-config --libs`   

${TESTDIR}/TestFiles/f3: ${TESTDIR}/system/tests/sysConfigTest.o ${TESTDIR}/system/tests/sysConfigTestRun.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS} -lldap -llber ../Debug/libsystem.so -lboost_filesystem -lboost_system -lboost_iostreams `cppunit-config --libs`   

${TESTDIR}/TestFiles/f6: ${TESTDIR}/utils/tests/utilsSecurityTest.o ${TESTDIR}/utils/tests/utilsSecurityTestRun.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f6 $^ ${LDLIBSOPTIONS} -lldap -llber ../Debug/libsystem.so -lboost_filesystem -lboost_system -lboost_iostreams `cppunit-config --libs`   


${TESTDIR}/data/tests/dataDatabaseTest.o: data/tests/dataDatabaseTest.cpp 
	${MKDIR} -p ${TESTDIR}/data/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/data/tests/dataDatabaseTest.o data/tests/dataDatabaseTest.cpp


${TESTDIR}/data/tests/dataDatabaseTestRun.o: data/tests/dataDatabaseTestRun.cpp 
	${MKDIR} -p ${TESTDIR}/data/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/data/tests/dataDatabaseTestRun.o data/tests/dataDatabaseTestRun.cpp


${TESTDIR}/data/tests/dataDateTimeTest.o: data/tests/dataDateTimeTest.cpp 
	${MKDIR} -p ${TESTDIR}/data/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/data/tests/dataDateTimeTest.o data/tests/dataDateTimeTest.cpp


${TESTDIR}/data/tests/dataDateTimeTestRun.o: data/tests/dataDateTimeTestRun.cpp 
	${MKDIR} -p ${TESTDIR}/data/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/data/tests/dataDateTimeTestRun.o data/tests/dataDateTimeTestRun.cpp


${TESTDIR}/data/tests/dataFieldTest.o: data/tests/dataFieldTest.cpp 
	${MKDIR} -p ${TESTDIR}/data/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/data/tests/dataFieldTest.o data/tests/dataFieldTest.cpp


${TESTDIR}/data/tests/dataFieldTestRun.o: data/tests/dataFieldTestRun.cpp 
	${MKDIR} -p ${TESTDIR}/data/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/data/tests/dataFieldTestRun.o data/tests/dataFieldTestRun.cpp


${TESTDIR}/data/tests/dataRowTest.o: data/tests/dataRowTest.cpp 
	${MKDIR} -p ${TESTDIR}/data/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/data/tests/dataRowTest.o data/tests/dataRowTest.cpp


${TESTDIR}/data/tests/dataRowTestRun.o: data/tests/dataRowTestRun.cpp 
	${MKDIR} -p ${TESTDIR}/data/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/data/tests/dataRowTestRun.o data/tests/dataRowTestRun.cpp


${TESTDIR}/data/tests/dataServerTest.o: data/tests/dataServerTest.cpp 
	${MKDIR} -p ${TESTDIR}/data/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/data/tests/dataServerTest.o data/tests/dataServerTest.cpp


${TESTDIR}/data/tests/dataServerTestRun.o: data/tests/dataServerTestRun.cpp 
	${MKDIR} -p ${TESTDIR}/data/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/data/tests/dataServerTestRun.o data/tests/dataServerTestRun.cpp


${TESTDIR}/ldap/tests/ldapDataTest.o: ldap/tests/ldapDataTest.cpp 
	${MKDIR} -p ${TESTDIR}/ldap/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/ldap/tests/ldapDataTest.o ldap/tests/ldapDataTest.cpp


${TESTDIR}/ldap/tests/ldapDataTestRun.o: ldap/tests/ldapDataTestRun.cpp 
	${MKDIR} -p ${TESTDIR}/ldap/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/ldap/tests/ldapDataTestRun.o ldap/tests/ldapDataTestRun.cpp


${TESTDIR}/ldap/tests/ldapServerTest.o: ldap/tests/ldapServerTest.cpp 
	${MKDIR} -p ${TESTDIR}/ldap/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/ldap/tests/ldapServerTest.o ldap/tests/ldapServerTest.cpp


${TESTDIR}/ldap/tests/ldapServerTestRun.o: ldap/tests/ldapServerTestRun.cpp 
	${MKDIR} -p ${TESTDIR}/ldap/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/ldap/tests/ldapServerTestRun.o ldap/tests/ldapServerTestRun.cpp


${TESTDIR}/ldap/tests/ldpAttributesTest.o: ldap/tests/ldpAttributesTest.cpp 
	${MKDIR} -p ${TESTDIR}/ldap/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -I. -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/ldap/tests/ldpAttributesTest.o ldap/tests/ldpAttributesTest.cpp


${TESTDIR}/ldap/tests/ldpAttributesTestRun.o: ldap/tests/ldpAttributesTestRun.cpp 
	${MKDIR} -p ${TESTDIR}/ldap/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -I. -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/ldap/tests/ldpAttributesTestRun.o ldap/tests/ldpAttributesTestRun.cpp


${TESTDIR}/ldap/tests/ldpBaseDataTest.o: ldap/tests/ldpBaseDataTest.cpp 
	${MKDIR} -p ${TESTDIR}/ldap/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/ldap/tests/ldpBaseDataTest.o ldap/tests/ldpBaseDataTest.cpp


${TESTDIR}/ldap/tests/ldpBaseDataTestRun.o: ldap/tests/ldpBaseDataTestRun.cpp 
	${MKDIR} -p ${TESTDIR}/ldap/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/ldap/tests/ldpBaseDataTestRun.o ldap/tests/ldpBaseDataTestRun.cpp


${TESTDIR}/system/tests/sysConfigTest.o: system/tests/sysConfigTest.cpp 
	${MKDIR} -p ${TESTDIR}/system/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/system/tests/sysConfigTest.o system/tests/sysConfigTest.cpp


${TESTDIR}/system/tests/sysConfigTestRun.o: system/tests/sysConfigTestRun.cpp 
	${MKDIR} -p ${TESTDIR}/system/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/system/tests/sysConfigTestRun.o system/tests/sysConfigTestRun.cpp


${TESTDIR}/utils/tests/utilsSecurityTest.o: utils/tests/utilsSecurityTest.cpp 
	${MKDIR} -p ${TESTDIR}/utils/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/utils/tests/utilsSecurityTest.o utils/tests/utilsSecurityTest.cpp


${TESTDIR}/utils/tests/utilsSecurityTestRun.o: utils/tests/utilsSecurityTestRun.cpp 
	${MKDIR} -p ${TESTDIR}/utils/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/utils/tests/utilsSecurityTestRun.o utils/tests/utilsSecurityTestRun.cpp


${OBJECTDIR}/data/database_nomain.o: ${OBJECTDIR}/data/database.o data/database.cpp 
	${MKDIR} -p ${OBJECTDIR}/data
	@NMOUTPUT=`${NM} ${OBJECTDIR}/data/database.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data/database_nomain.o data/database.cpp;\
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
	    $(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data/dateTime_nomain.o data/dateTime.cpp;\
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
	    $(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data/field_nomain.o data/field.cpp;\
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
	    $(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data/row_nomain.o data/row.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/data/row.o ${OBJECTDIR}/data/row_nomain.o;\
	fi

${OBJECTDIR}/data/sqlserver_nomain.o: ${OBJECTDIR}/data/sqlserver.o data/sqlserver.cpp 
	${MKDIR} -p ${OBJECTDIR}/data
	@NMOUTPUT=`${NM} ${OBJECTDIR}/data/sqlserver.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data/sqlserver_nomain.o data/sqlserver.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/data/sqlserver.o ${OBJECTDIR}/data/sqlserver_nomain.o;\
	fi

${OBJECTDIR}/gui/application_nomain.o: ${OBJECTDIR}/gui/application.o gui/application.cpp 
	${MKDIR} -p ${OBJECTDIR}/gui
	@NMOUTPUT=`${NM} ${OBJECTDIR}/gui/application.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gui/application_nomain.o gui/application.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/gui/application.o ${OBJECTDIR}/gui/application_nomain.o;\
	fi

${OBJECTDIR}/ldap/account_nomain.o: ${OBJECTDIR}/ldap/account.o ldap/account.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ldap/account.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/account_nomain.o ldap/account.cpp;\
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
	    $(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/attributes_nomain.o ldap/attributes.cpp;\
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
	    $(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/data_nomain.o ldap/data.cpp;\
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
	    $(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/dataset_nomain.o ldap/dataset.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ldap/dataset.o ${OBJECTDIR}/ldap/dataset_nomain.o;\
	fi

${OBJECTDIR}/ldap/editableGroup_nomain.o: ${OBJECTDIR}/ldap/editableGroup.o ldap/editableGroup.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ldap/editableGroup.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/editableGroup_nomain.o ldap/editableGroup.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ldap/editableGroup.o ${OBJECTDIR}/ldap/editableGroup_nomain.o;\
	fi

${OBJECTDIR}/ldap/group_nomain.o: ${OBJECTDIR}/ldap/group.o ldap/group.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ldap/group.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/group_nomain.o ldap/group.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ldap/group.o ${OBJECTDIR}/ldap/group_nomain.o;\
	fi

${OBJECTDIR}/ldap/mailGroup_nomain.o: ${OBJECTDIR}/ldap/mailGroup.o ldap/mailGroup.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ldap/mailGroup.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/mailGroup_nomain.o ldap/mailGroup.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ldap/mailGroup.o ${OBJECTDIR}/ldap/mailGroup_nomain.o;\
	fi

${OBJECTDIR}/ldap/server_nomain.o: ${OBJECTDIR}/ldap/server.o ldap/server.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ldap/server.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/server_nomain.o ldap/server.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ldap/server.o ${OBJECTDIR}/ldap/server_nomain.o;\
	fi

${OBJECTDIR}/system/process_nomain.o: ${OBJECTDIR}/system/process.o system/process.cpp 
	${MKDIR} -p ${OBJECTDIR}/system
	@NMOUTPUT=`${NM} ${OBJECTDIR}/system/process.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/process_nomain.o system/process.cpp;\
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
	    $(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/workDir_nomain.o system/workDir.cpp;\
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
	    $(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/config_nomain.o utils/config.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/utils/config.o ${OBJECTDIR}/utils/config_nomain.o;\
	fi

${OBJECTDIR}/utils/container_nomain.o: ${OBJECTDIR}/utils/container.o utils/container.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	@NMOUTPUT=`${NM} ${OBJECTDIR}/utils/container.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/container_nomain.o utils/container.cpp;\
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
	    $(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/convert_nomain.o utils/convert.cpp;\
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
	    $(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/log_nomain.o utils/log.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/utils/log.o ${OBJECTDIR}/utils/log_nomain.o;\
	fi

${OBJECTDIR}/utils/security_nomain.o: ${OBJECTDIR}/utils/security.o utils/security.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	@NMOUTPUT=`${NM} ${OBJECTDIR}/utils/security.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Werror -I. -I../dependencies/boost_process -I/usr/include -std=c++11 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/security_nomain.o utils/security.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/utils/security.o ${OBJECTDIR}/utils/security_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f10 || true; \
	    ${TESTDIR}/TestFiles/f11 || true; \
	    ${TESTDIR}/TestFiles/f8 || true; \
	    ${TESTDIR}/TestFiles/f9 || true; \
	    ${TESTDIR}/TestFiles/f7 || true; \
	    ${TESTDIR}/TestFiles/f5 || true; \
	    ${TESTDIR}/TestFiles/f4 || true; \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f3 || true; \
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
