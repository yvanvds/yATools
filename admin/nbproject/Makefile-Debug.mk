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
	${OBJECTDIR}/_ext/1736800395/password.o \
	${OBJECTDIR}/_ext/1736800395/show.o \
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
LDLIBSOPTIONS=-Wl,-rpath,/home/yvan/github/yATools/libadmintools/../Debug -L/home/yvan/github/yATools/libadmintools/../Debug -lsystem -lboost_program_options

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/admin

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/admin: /home/yvan/github/yATools/libadmintools/../Debug/libsystem.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/admin: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/admin ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/1736800395/password.o: /home/yvan/github/yATools/admin/password.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1736800395
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1736800395/password.o /home/yvan/github/yATools/admin/password.cpp

${OBJECTDIR}/_ext/1736800395/show.o: /home/yvan/github/yATools/admin/show.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1736800395
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1736800395/show.o /home/yvan/github/yATools/admin/show.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:
	cd /home/yvan/github/yATools/libadmintools && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/admin

# Subprojects
.clean-subprojects:
	cd /home/yvan/github/yATools/libadmintools && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
