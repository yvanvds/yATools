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
	${OBJECTDIR}/configuration.o \
	${OBJECTDIR}/dataconnect.o \
	${OBJECTDIR}/download.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/removeDialog.o \
	${OBJECTDIR}/review.o \
	${OBJECTDIR}/yearbookAdmin.o


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
LDLIBSOPTIONS=-L/usr/lib/x86_64-linux-gnu -L/usr/lib -L/usr/local/lib -Wl,-rpath,../libadmintools/../Debug -L../libadmintools/../Debug -lsystem -lwthttp -lwt -lboost_system -lboost_filesystem -lboost_iostreams -lboost_program_options -llber -lldap

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/yearbookadmin

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/yearbookadmin: ../libadmintools/../Debug/libsystem.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/yearbookadmin: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/yearbookadmin ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/configuration.o: configuration.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../libadmintools -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/configuration.o configuration.cpp

${OBJECTDIR}/dataconnect.o: dataconnect.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../libadmintools -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/dataconnect.o dataconnect.cpp

${OBJECTDIR}/download.o: download.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../libadmintools -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/download.o download.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../libadmintools -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/removeDialog.o: removeDialog.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../libadmintools -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/removeDialog.o removeDialog.cpp

${OBJECTDIR}/review.o: review.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../libadmintools -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/review.o review.cpp

${OBJECTDIR}/yearbookAdmin.o: yearbookAdmin.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../libadmintools -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/yearbookAdmin.o yearbookAdmin.cpp

# Subprojects
.build-subprojects:
	cd ../libadmintools && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/yearbookadmin

# Subprojects
.clean-subprojects:
	cd ../libadmintools && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
