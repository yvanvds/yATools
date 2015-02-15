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
	${OBJECTDIR}/accountManager.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/webLogin.o


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
LDLIBSOPTIONS=-L/usr/lib/x86_64-linux-gnu -L/usr/lib -L/usr/local/lib -lwtfcgi -lwt -lldap -llber -lboost_system -lboost_filesystem -lboost_iostreams -lboost_program_options -lboost_signals -Wl,-rpath,../libadmintools/dist/Release/GNU-Linux-x86 -L../libadmintools/dist/Release/GNU-Linux-x86 -llibadmintools

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/weblogin

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/weblogin: ../libadmintools/dist/Release/GNU-Linux-x86/liblibadmintools.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/weblogin: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/weblogin ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/accountManager.o: accountManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/accountManager.o accountManager.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/webLogin.o: webLogin.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/webLogin.o webLogin.cpp

# Subprojects
.build-subprojects:
	cd ../libadmintools && ${MAKE}  -f Makefile CONF=Release

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/weblogin

# Subprojects
.clean-subprojects:
	cd ../libadmintools && ${MAKE}  -f Makefile CONF=Release clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
