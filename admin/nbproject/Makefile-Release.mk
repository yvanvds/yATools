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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1736800395/password.o \
	${OBJECTDIR}/_ext/1736800395/show.o \
	${OBJECTDIR}/addGroup.o \
	${OBJECTDIR}/addUser.o \
	${OBJECTDIR}/debugFunctions.o \
	${OBJECTDIR}/find.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/proxyManager.o \
	${OBJECTDIR}/removeGroup.o \
	${OBJECTDIR}/removeUser.o \
	${OBJECTDIR}/renameUser.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-Wl,-rpath,/home/yvan/github/yATools/libadmintools/dist/Release/GNU-Linux-x86 -L/home/yvan/github/yATools/libadmintools/dist/Release/GNU-Linux-x86 -llibadmintools -lboost_locale

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/admin

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/admin: /home/yvan/github/yATools/libadmintools/dist/Release/GNU-Linux-x86/liblibadmintools.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/admin: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/admin ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/1736800395/password.o: /home/yvan/github/yATools/admin/password.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1736800395
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1736800395/password.o /home/yvan/github/yATools/admin/password.cpp

${OBJECTDIR}/_ext/1736800395/show.o: /home/yvan/github/yATools/admin/show.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1736800395
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1736800395/show.o /home/yvan/github/yATools/admin/show.cpp

${OBJECTDIR}/addGroup.o: addGroup.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/addGroup.o addGroup.cpp

${OBJECTDIR}/addUser.o: addUser.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/addUser.o addUser.cpp

${OBJECTDIR}/debugFunctions.o: debugFunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/debugFunctions.o debugFunctions.cpp

${OBJECTDIR}/find.o: find.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/find.o find.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/proxyManager.o: proxyManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/proxyManager.o proxyManager.cpp

${OBJECTDIR}/removeGroup.o: removeGroup.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/removeGroup.o removeGroup.cpp

${OBJECTDIR}/removeUser.o: removeUser.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/removeUser.o removeUser.cpp

${OBJECTDIR}/renameUser.o: renameUser.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/renameUser.o renameUser.cpp

# Subprojects
.build-subprojects:
	cd /home/yvan/github/yATools/libadmintools && ${MAKE}  -f Makefile CONF=Release

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/admin

# Subprojects
.clean-subprojects:
	cd /home/yvan/github/yATools/libadmintools && ${MAKE}  -f Makefile CONF=Release clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
