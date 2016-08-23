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
	${OBJECTDIR}/account/changeName.o \
	${OBJECTDIR}/account/changePassword.o \
	${OBJECTDIR}/application.o \
	${OBJECTDIR}/auth/authModel.o \
	${OBJECTDIR}/auth/authService.o \
	${OBJECTDIR}/auth/authWidget.o \
	${OBJECTDIR}/auth/passwordService.o \
	${OBJECTDIR}/auth/session.o \
	${OBJECTDIR}/auth/user.o \
	${OBJECTDIR}/base/imageConvert.o \
	${OBJECTDIR}/base/stackPage.o \
	${OBJECTDIR}/base/stackPageManager.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/proxyManager.o \
	${OBJECTDIR}/staffManager/newStaff.o \
	${OBJECTDIR}/staffManager/staffList.o \
	${OBJECTDIR}/studentPasswords/passwordFile.o \
	${OBJECTDIR}/studentPasswords/studentPasswords.o \
	${OBJECTDIR}/topContent.o \
	${OBJECTDIR}/wisaImport.o \
	${OBJECTDIR}/wisaImport/wisaChangeClassMembers.o \
	${OBJECTDIR}/wisaImport/wisaCommitClasses.o \
	${OBJECTDIR}/wisaImport/wisaCommitStudents.o \
	${OBJECTDIR}/wisaImport/wisaCompareClasses.o \
	${OBJECTDIR}/wisaImport/wisaCompareFile.o \
	${OBJECTDIR}/wisaImport/wisaCompareNames.o \
	${OBJECTDIR}/wisaImport/wisaConfirmSubmit.o \
	${OBJECTDIR}/wisaImport/wisaNewGroups.o \
	${OBJECTDIR}/wisaImport/wisaNoID.o \
	${OBJECTDIR}/wisaImport/wisaParseClassFile.o \
	${OBJECTDIR}/wisaImport/wisaParseStudentFile.o \
	${OBJECTDIR}/wisaImport/wisaUpload.o \
	${OBJECTDIR}/yearbook/yearbook.o \
	${OBJECTDIR}/yearbook/yearbookConfig.o \
	${OBJECTDIR}/yearbook/yearbookConfirmRemove.o \
	${OBJECTDIR}/yearbook/yearbookDB.o \
	${OBJECTDIR}/yearbook/yearbookDone.o \
	${OBJECTDIR}/yearbook/yearbookDownload.o \
	${OBJECTDIR}/yearbook/yearbookMailinglist.o \
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
LDLIBSOPTIONS=-L/usr/lib/x86_64-linux-gnu -L/usr/lib -L/usr/local/lib -lwthttp -lwt -lwtdbo -lwtdbomysql -Wl,-rpath,../libadmintools/../Debug -L../libadmintools/../Debug -lsystem -lboost_system -lboost_filesystem -lboost_iostreams -lboost_program_options -lboost_signals -llber -lldap -lboost_locale -lpng -ljpeg -lpthread

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/weblogin

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/weblogin: ../libadmintools/../Debug/libsystem.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/weblogin: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/weblogin ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/account/changeName.o: account/changeName.cpp 
	${MKDIR} -p ${OBJECTDIR}/account
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/account/changeName.o account/changeName.cpp

${OBJECTDIR}/account/changePassword.o: account/changePassword.cpp 
	${MKDIR} -p ${OBJECTDIR}/account
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/account/changePassword.o account/changePassword.cpp

${OBJECTDIR}/application.o: application.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/application.o application.cpp

${OBJECTDIR}/auth/authModel.o: auth/authModel.cpp 
	${MKDIR} -p ${OBJECTDIR}/auth
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/auth/authModel.o auth/authModel.cpp

${OBJECTDIR}/auth/authService.o: auth/authService.cpp 
	${MKDIR} -p ${OBJECTDIR}/auth
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/auth/authService.o auth/authService.cpp

${OBJECTDIR}/auth/authWidget.o: auth/authWidget.cpp 
	${MKDIR} -p ${OBJECTDIR}/auth
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/auth/authWidget.o auth/authWidget.cpp

${OBJECTDIR}/auth/passwordService.o: auth/passwordService.cpp 
	${MKDIR} -p ${OBJECTDIR}/auth
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/auth/passwordService.o auth/passwordService.cpp

${OBJECTDIR}/auth/session.o: auth/session.cpp 
	${MKDIR} -p ${OBJECTDIR}/auth
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/auth/session.o auth/session.cpp

${OBJECTDIR}/auth/user.o: auth/user.cpp 
	${MKDIR} -p ${OBJECTDIR}/auth
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/auth/user.o auth/user.cpp

${OBJECTDIR}/base/imageConvert.o: base/imageConvert.cpp 
	${MKDIR} -p ${OBJECTDIR}/base
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/base/imageConvert.o base/imageConvert.cpp

${OBJECTDIR}/base/stackPage.o: base/stackPage.cpp 
	${MKDIR} -p ${OBJECTDIR}/base
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/base/stackPage.o base/stackPage.cpp

${OBJECTDIR}/base/stackPageManager.o: base/stackPageManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/base
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/base/stackPageManager.o base/stackPageManager.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/proxyManager.o: proxyManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/proxyManager.o proxyManager.cpp

${OBJECTDIR}/staffManager/newStaff.o: staffManager/newStaff.cpp 
	${MKDIR} -p ${OBJECTDIR}/staffManager
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/staffManager/newStaff.o staffManager/newStaff.cpp

${OBJECTDIR}/staffManager/staffList.o: staffManager/staffList.cpp 
	${MKDIR} -p ${OBJECTDIR}/staffManager
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/staffManager/staffList.o staffManager/staffList.cpp

${OBJECTDIR}/studentPasswords/passwordFile.o: studentPasswords/passwordFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/studentPasswords
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/studentPasswords/passwordFile.o studentPasswords/passwordFile.cpp

${OBJECTDIR}/studentPasswords/studentPasswords.o: studentPasswords/studentPasswords.cpp 
	${MKDIR} -p ${OBJECTDIR}/studentPasswords
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/studentPasswords/studentPasswords.o studentPasswords/studentPasswords.cpp

${OBJECTDIR}/topContent.o: topContent.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/topContent.o topContent.cpp

${OBJECTDIR}/wisaImport.o: wisaImport.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/wisaImport.o wisaImport.cpp

${OBJECTDIR}/wisaImport/wisaChangeClassMembers.o: wisaImport/wisaChangeClassMembers.cpp 
	${MKDIR} -p ${OBJECTDIR}/wisaImport
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/wisaImport/wisaChangeClassMembers.o wisaImport/wisaChangeClassMembers.cpp

${OBJECTDIR}/wisaImport/wisaCommitClasses.o: wisaImport/wisaCommitClasses.cpp 
	${MKDIR} -p ${OBJECTDIR}/wisaImport
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/wisaImport/wisaCommitClasses.o wisaImport/wisaCommitClasses.cpp

${OBJECTDIR}/wisaImport/wisaCommitStudents.o: wisaImport/wisaCommitStudents.cpp 
	${MKDIR} -p ${OBJECTDIR}/wisaImport
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/wisaImport/wisaCommitStudents.o wisaImport/wisaCommitStudents.cpp

${OBJECTDIR}/wisaImport/wisaCompareClasses.o: wisaImport/wisaCompareClasses.cpp 
	${MKDIR} -p ${OBJECTDIR}/wisaImport
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/wisaImport/wisaCompareClasses.o wisaImport/wisaCompareClasses.cpp

${OBJECTDIR}/wisaImport/wisaCompareFile.o: wisaImport/wisaCompareFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/wisaImport
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/wisaImport/wisaCompareFile.o wisaImport/wisaCompareFile.cpp

${OBJECTDIR}/wisaImport/wisaCompareNames.o: wisaImport/wisaCompareNames.cpp 
	${MKDIR} -p ${OBJECTDIR}/wisaImport
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/wisaImport/wisaCompareNames.o wisaImport/wisaCompareNames.cpp

${OBJECTDIR}/wisaImport/wisaConfirmSubmit.o: wisaImport/wisaConfirmSubmit.cpp 
	${MKDIR} -p ${OBJECTDIR}/wisaImport
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/wisaImport/wisaConfirmSubmit.o wisaImport/wisaConfirmSubmit.cpp

${OBJECTDIR}/wisaImport/wisaNewGroups.o: wisaImport/wisaNewGroups.cpp 
	${MKDIR} -p ${OBJECTDIR}/wisaImport
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/wisaImport/wisaNewGroups.o wisaImport/wisaNewGroups.cpp

${OBJECTDIR}/wisaImport/wisaNoID.o: wisaImport/wisaNoID.cpp 
	${MKDIR} -p ${OBJECTDIR}/wisaImport
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/wisaImport/wisaNoID.o wisaImport/wisaNoID.cpp

${OBJECTDIR}/wisaImport/wisaParseClassFile.o: wisaImport/wisaParseClassFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/wisaImport
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/wisaImport/wisaParseClassFile.o wisaImport/wisaParseClassFile.cpp

${OBJECTDIR}/wisaImport/wisaParseStudentFile.o: wisaImport/wisaParseStudentFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/wisaImport
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/wisaImport/wisaParseStudentFile.o wisaImport/wisaParseStudentFile.cpp

${OBJECTDIR}/wisaImport/wisaUpload.o: wisaImport/wisaUpload.cpp 
	${MKDIR} -p ${OBJECTDIR}/wisaImport
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/wisaImport/wisaUpload.o wisaImport/wisaUpload.cpp

${OBJECTDIR}/yearbook/yearbook.o: yearbook/yearbook.cpp 
	${MKDIR} -p ${OBJECTDIR}/yearbook
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/yearbook/yearbook.o yearbook/yearbook.cpp

${OBJECTDIR}/yearbook/yearbookConfig.o: yearbook/yearbookConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/yearbook
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/yearbook/yearbookConfig.o yearbook/yearbookConfig.cpp

${OBJECTDIR}/yearbook/yearbookConfirmRemove.o: yearbook/yearbookConfirmRemove.cpp 
	${MKDIR} -p ${OBJECTDIR}/yearbook
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/yearbook/yearbookConfirmRemove.o yearbook/yearbookConfirmRemove.cpp

${OBJECTDIR}/yearbook/yearbookDB.o: yearbook/yearbookDB.cpp 
	${MKDIR} -p ${OBJECTDIR}/yearbook
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/yearbook/yearbookDB.o yearbook/yearbookDB.cpp

${OBJECTDIR}/yearbook/yearbookDone.o: yearbook/yearbookDone.cpp 
	${MKDIR} -p ${OBJECTDIR}/yearbook
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/yearbook/yearbookDone.o yearbook/yearbookDone.cpp

${OBJECTDIR}/yearbook/yearbookDownload.o: yearbook/yearbookDownload.cpp 
	${MKDIR} -p ${OBJECTDIR}/yearbook
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/yearbook/yearbookDownload.o yearbook/yearbookDownload.cpp

${OBJECTDIR}/yearbook/yearbookMailinglist.o: yearbook/yearbookMailinglist.cpp 
	${MKDIR} -p ${OBJECTDIR}/yearbook
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/yearbook/yearbookMailinglist.o yearbook/yearbookMailinglist.cpp

${OBJECTDIR}/yearbook/yearbookPhoto.o: yearbook/yearbookPhoto.cpp 
	${MKDIR} -p ${OBJECTDIR}/yearbook
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/yearbook/yearbookPhoto.o yearbook/yearbookPhoto.cpp

${OBJECTDIR}/yearbook/yearbookQuestion.o: yearbook/yearbookQuestion.cpp 
	${MKDIR} -p ${OBJECTDIR}/yearbook
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/yearbook/yearbookQuestion.o yearbook/yearbookQuestion.cpp

${OBJECTDIR}/yearbook/yearbookReview.o: yearbook/yearbookReview.cpp 
	${MKDIR} -p ${OBJECTDIR}/yearbook
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/yearbook/yearbookReview.o yearbook/yearbookReview.cpp

${OBJECTDIR}/yearbook/yearbookVerifyAccount.o: yearbook/yearbookVerifyAccount.cpp 
	${MKDIR} -p ${OBJECTDIR}/yearbook
	${RM} "$@.d"
	$(COMPILE.cc) -g -DDEBUG -I../libadmintools -I/usr/local/include -I../build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/yearbook/yearbookVerifyAccount.o yearbook/yearbookVerifyAccount.cpp

# Subprojects
.build-subprojects:
	cd ../libadmintools && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/weblogin

# Subprojects
.clean-subprojects:
	cd ../libadmintools && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
