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
	${OBJECTDIR}/_ext/1764173701/configuration.o \
	${OBJECTDIR}/_ext/1764173701/dataconnect.o \
	${OBJECTDIR}/_ext/1764173701/review.o \
	${OBJECTDIR}/_ext/1764173701/yearbookAdmin.o \
	${OBJECTDIR}/main.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/yearbookadmin

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/yearbookadmin: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/yearbookadmin ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/1764173701/configuration.o: /home/yvan/github/yATools/yearbookAdmin/configuration.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1764173701
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1764173701/configuration.o /home/yvan/github/yATools/yearbookAdmin/configuration.cpp

${OBJECTDIR}/_ext/1764173701/dataconnect.o: /home/yvan/github/yATools/yearbookAdmin/dataconnect.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1764173701
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1764173701/dataconnect.o /home/yvan/github/yATools/yearbookAdmin/dataconnect.cpp

${OBJECTDIR}/_ext/1764173701/review.o: /home/yvan/github/yATools/yearbookAdmin/review.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1764173701
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1764173701/review.o /home/yvan/github/yATools/yearbookAdmin/review.cpp

${OBJECTDIR}/_ext/1764173701/yearbookAdmin.o: /home/yvan/github/yATools/yearbookAdmin/yearbookAdmin.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1764173701
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1764173701/yearbookAdmin.o /home/yvan/github/yATools/yearbookAdmin/yearbookAdmin.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/yearbookadmin

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
