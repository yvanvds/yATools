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
	${OBJECTDIR}/utils/log.o


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
LDLIBSOPTIONS=-lboost_system -lboost_filesystem -lboost_program_options

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../${CND_CONF}/libsystem.${CND_DLIB_EXT}

../${CND_CONF}/libsystem.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ../${CND_CONF}
	${LINK.cc} -o ../${CND_CONF}/libsystem.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/ldap/account.o: ldap/account.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/account.o ldap/account.cpp

${OBJECTDIR}/ldap/attributes.o: ldap/attributes.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/attributes.o ldap/attributes.cpp

${OBJECTDIR}/ldap/data.o: ldap/data.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/data.o ldap/data.cpp

${OBJECTDIR}/ldap/dataset.o: ldap/dataset.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/dataset.o ldap/dataset.cpp

${OBJECTDIR}/ldap/editableGroup.o: ldap/editableGroup.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/editableGroup.o ldap/editableGroup.cpp

${OBJECTDIR}/ldap/group.o: ldap/group.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/group.o ldap/group.cpp

${OBJECTDIR}/ldap/mailGroup.o: ldap/mailGroup.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/mailGroup.o ldap/mailGroup.cpp

${OBJECTDIR}/ldap/server.o: ldap/server.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/server.o ldap/server.cpp

${OBJECTDIR}/system/process.o: system/process.cpp 
	${MKDIR} -p ${OBJECTDIR}/system
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/process.o system/process.cpp

${OBJECTDIR}/system/workDir.o: system/workDir.cpp 
	${MKDIR} -p ${OBJECTDIR}/system
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/workDir.o system/workDir.cpp

${OBJECTDIR}/utils/config.o: utils/config.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/config.o utils/config.cpp

${OBJECTDIR}/utils/container.o: utils/container.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/container.o utils/container.cpp

${OBJECTDIR}/utils/log.o: utils/log.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -I. -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/log.o utils/log.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../${CND_CONF}/libsystem.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
