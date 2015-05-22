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
	${OBJECTDIR}/base/stackPage.o \
	${OBJECTDIR}/base/stackPageManager.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/proxyManager.o \
	${OBJECTDIR}/webLogin.o \
	${OBJECTDIR}/wisaImport.o \
	${OBJECTDIR}/wisaImport/wisaCommitChanges.o \
	${OBJECTDIR}/wisaImport/wisaCompareFile.o \
	${OBJECTDIR}/wisaImport/wisaCompareGroups.o \
	${OBJECTDIR}/wisaImport/wisaCompareNames.o \
	${OBJECTDIR}/wisaImport/wisaConfirmSubmit.o \
	${OBJECTDIR}/wisaImport/wisaNewGroups.o \
	${OBJECTDIR}/wisaImport/wisaNoID.o \
	${OBJECTDIR}/wisaImport/wisaParseFile.o \
	${OBJECTDIR}/wisaImport/wisaUpload.o \
	${OBJECTDIR}/yearbook/yearbook.o \
	${OBJECTDIR}/yearbook/yearbookConfig.o \
	${OBJECTDIR}/yearbook/yearbookConfirmRemove.o \
	${OBJECTDIR}/yearbook/yearbookDB.o \
	${OBJECTDIR}/yearbook/yearbookDone.o \
	${OBJECTDIR}/yearbook/yearbookDownload.o \
	${OBJECTDIR}/yearbook/yearbookPhoto.o \
	${OBJECTDIR}/yearbook/yearbookQuestion.o \
	${OBJECTDIR}/yearbook/yearbookReview.o \
	${OBJECTDIR}/yearbook/yearbookVerifyAccount.o


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
LDLIBSOPTIONS=-L/usr/lib/x86_64-linux-gnu -L/usr/lib -L/usr/local/lib -lwtfcgi -lwt -lldap -llber -lboost_system -lboost_filesystem -lboost_iostreams -lboost_program_options -lboost_signals -lboost_locale -Wl,-rpath,../libadmintools/dist/Release/GNU-Linux-x86 -L../libadmintools/dist/Release/GNU-Linux-x86 -llibadmintools

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

${OBJECTDIR}/base/stackPage.o: base/stackPage.cpp 
	${MKDIR} -p ${OBJECTDIR}/base
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/base/stackPage.o base/stackPage.cpp

${OBJECTDIR}/base/stackPageManager.o: base/stackPageManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/base
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/base/stackPageManager.o base/stackPageManager.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/proxyManager.o: proxyManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/proxyManager.o proxyManager.cpp

${OBJECTDIR}/webLogin.o: webLogin.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/webLogin.o webLogin.cpp

${OBJECTDIR}/wisaImport.o: wisaImport.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/wisaImport.o wisaImport.cpp

${OBJECTDIR}/wisaImport/wisaCommitChanges.o: wisaImport/wisaCommitChanges.cpp 
	${MKDIR} -p ${OBJECTDIR}/wisaImport
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/wisaImport/wisaCommitChanges.o wisaImport/wisaCommitChanges.cpp

${OBJECTDIR}/wisaImport/wisaCompareFile.o: wisaImport/wisaCompareFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/wisaImport
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/wisaImport/wisaCompareFile.o wisaImport/wisaCompareFile.cpp

${OBJECTDIR}/wisaImport/wisaCompareGroups.o: wisaImport/wisaCompareGroups.cpp 
	${MKDIR} -p ${OBJECTDIR}/wisaImport
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/wisaImport/wisaCompareGroups.o wisaImport/wisaCompareGroups.cpp

${OBJECTDIR}/wisaImport/wisaCompareNames.o: wisaImport/wisaCompareNames.cpp 
	${MKDIR} -p ${OBJECTDIR}/wisaImport
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/wisaImport/wisaCompareNames.o wisaImport/wisaCompareNames.cpp

${OBJECTDIR}/wisaImport/wisaConfirmSubmit.o: wisaImport/wisaConfirmSubmit.cpp 
	${MKDIR} -p ${OBJECTDIR}/wisaImport
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/wisaImport/wisaConfirmSubmit.o wisaImport/wisaConfirmSubmit.cpp

${OBJECTDIR}/wisaImport/wisaNewGroups.o: wisaImport/wisaNewGroups.cpp 
	${MKDIR} -p ${OBJECTDIR}/wisaImport
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/wisaImport/wisaNewGroups.o wisaImport/wisaNewGroups.cpp

${OBJECTDIR}/wisaImport/wisaNoID.o: wisaImport/wisaNoID.cpp 
	${MKDIR} -p ${OBJECTDIR}/wisaImport
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/wisaImport/wisaNoID.o wisaImport/wisaNoID.cpp

${OBJECTDIR}/wisaImport/wisaParseFile.o: wisaImport/wisaParseFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/wisaImport
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/wisaImport/wisaParseFile.o wisaImport/wisaParseFile.cpp

${OBJECTDIR}/wisaImport/wisaUpload.o: wisaImport/wisaUpload.cpp 
	${MKDIR} -p ${OBJECTDIR}/wisaImport
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/wisaImport/wisaUpload.o wisaImport/wisaUpload.cpp

${OBJECTDIR}/yearbook/yearbook.o: yearbook/yearbook.cpp 
	${MKDIR} -p ${OBJECTDIR}/yearbook
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/yearbook/yearbook.o yearbook/yearbook.cpp

${OBJECTDIR}/yearbook/yearbookConfig.o: yearbook/yearbookConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/yearbook
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/yearbook/yearbookConfig.o yearbook/yearbookConfig.cpp

${OBJECTDIR}/yearbook/yearbookConfirmRemove.o: yearbook/yearbookConfirmRemove.cpp 
	${MKDIR} -p ${OBJECTDIR}/yearbook
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/yearbook/yearbookConfirmRemove.o yearbook/yearbookConfirmRemove.cpp

${OBJECTDIR}/yearbook/yearbookDB.o: yearbook/yearbookDB.cpp 
	${MKDIR} -p ${OBJECTDIR}/yearbook
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/yearbook/yearbookDB.o yearbook/yearbookDB.cpp

${OBJECTDIR}/yearbook/yearbookDone.o: yearbook/yearbookDone.cpp 
	${MKDIR} -p ${OBJECTDIR}/yearbook
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/yearbook/yearbookDone.o yearbook/yearbookDone.cpp

${OBJECTDIR}/yearbook/yearbookDownload.o: yearbook/yearbookDownload.cpp 
	${MKDIR} -p ${OBJECTDIR}/yearbook
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/yearbook/yearbookDownload.o yearbook/yearbookDownload.cpp

${OBJECTDIR}/yearbook/yearbookPhoto.o: yearbook/yearbookPhoto.cpp 
	${MKDIR} -p ${OBJECTDIR}/yearbook
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/yearbook/yearbookPhoto.o yearbook/yearbookPhoto.cpp

${OBJECTDIR}/yearbook/yearbookQuestion.o: yearbook/yearbookQuestion.cpp 
	${MKDIR} -p ${OBJECTDIR}/yearbook
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/yearbook/yearbookQuestion.o yearbook/yearbookQuestion.cpp

${OBJECTDIR}/yearbook/yearbookReview.o: yearbook/yearbookReview.cpp 
	${MKDIR} -p ${OBJECTDIR}/yearbook
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/yearbook/yearbookReview.o yearbook/yearbookReview.cpp

${OBJECTDIR}/yearbook/yearbookVerifyAccount.o: yearbook/yearbookVerifyAccount.cpp 
	${MKDIR} -p ${OBJECTDIR}/yearbook
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../libadmintools -I/usr/local/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/yearbook/yearbookVerifyAccount.o yearbook/yearbookVerifyAccount.cpp

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
