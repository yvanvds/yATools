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

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f4 \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f3

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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblibadmintools.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblibadmintools.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblibadmintools.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/ldap/account.o: ldap/account.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/account.o ldap/account.cpp

${OBJECTDIR}/ldap/attributes.o: ldap/attributes.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/attributes.o ldap/attributes.cpp

${OBJECTDIR}/ldap/data.o: ldap/data.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/data.o ldap/data.cpp

${OBJECTDIR}/ldap/dataset.o: ldap/dataset.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/dataset.o ldap/dataset.cpp

${OBJECTDIR}/ldap/editableGroup.o: ldap/editableGroup.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/editableGroup.o ldap/editableGroup.cpp

${OBJECTDIR}/ldap/group.o: ldap/group.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/group.o ldap/group.cpp

${OBJECTDIR}/ldap/mailGroup.o: ldap/mailGroup.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/mailGroup.o ldap/mailGroup.cpp

${OBJECTDIR}/ldap/server.o: ldap/server.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/server.o ldap/server.cpp

${OBJECTDIR}/system/process.o: system/process.cpp 
	${MKDIR} -p ${OBJECTDIR}/system
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/process.o system/process.cpp

${OBJECTDIR}/system/workDir.o: system/workDir.cpp 
	${MKDIR} -p ${OBJECTDIR}/system
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/workDir.o system/workDir.cpp

${OBJECTDIR}/utils/config.o: utils/config.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/config.o utils/config.cpp

${OBJECTDIR}/utils/container.o: utils/container.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/container.o utils/container.cpp

${OBJECTDIR}/utils/log.o: utils/log.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/log.o utils/log.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f4: ${TESTDIR}/ldap/tests/ldapServerTest.o ${TESTDIR}/ldap/tests/ldapServerTestRun.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f4 $^ ${LDLIBSOPTIONS} `cppunit-config --libs`   

${TESTDIR}/TestFiles/f1: ${TESTDIR}/ldap/tests/ldpAttributesTest.o ${TESTDIR}/ldap/tests/ldpAttributesTestRun.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} `cppunit-config --libs`   

${TESTDIR}/TestFiles/f2: ${TESTDIR}/ldap/tests/ldpBaseDataTest.o ${TESTDIR}/ldap/tests/ldpBaseDataTestRun.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} `cppunit-config --libs`   

${TESTDIR}/TestFiles/f3: ${TESTDIR}/system/tests/sysConfigTest.o ${TESTDIR}/system/tests/sysConfigTestRun.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS} `cppunit-config --libs`   


${TESTDIR}/ldap/tests/ldapServerTest.o: ldap/tests/ldapServerTest.cpp 
	${MKDIR} -p ${TESTDIR}/ldap/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/ldap/tests/ldapServerTest.o ldap/tests/ldapServerTest.cpp


${TESTDIR}/ldap/tests/ldapServerTestRun.o: ldap/tests/ldapServerTestRun.cpp 
	${MKDIR} -p ${TESTDIR}/ldap/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/ldap/tests/ldapServerTestRun.o ldap/tests/ldapServerTestRun.cpp


${TESTDIR}/ldap/tests/ldpAttributesTest.o: ldap/tests/ldpAttributesTest.cpp 
	${MKDIR} -p ${TESTDIR}/ldap/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/ldap/tests/ldpAttributesTest.o ldap/tests/ldpAttributesTest.cpp


${TESTDIR}/ldap/tests/ldpAttributesTestRun.o: ldap/tests/ldpAttributesTestRun.cpp 
	${MKDIR} -p ${TESTDIR}/ldap/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/ldap/tests/ldpAttributesTestRun.o ldap/tests/ldpAttributesTestRun.cpp


${TESTDIR}/ldap/tests/ldpBaseDataTest.o: ldap/tests/ldpBaseDataTest.cpp 
	${MKDIR} -p ${TESTDIR}/ldap/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/ldap/tests/ldpBaseDataTest.o ldap/tests/ldpBaseDataTest.cpp


${TESTDIR}/ldap/tests/ldpBaseDataTestRun.o: ldap/tests/ldpBaseDataTestRun.cpp 
	${MKDIR} -p ${TESTDIR}/ldap/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/ldap/tests/ldpBaseDataTestRun.o ldap/tests/ldpBaseDataTestRun.cpp


${TESTDIR}/system/tests/sysConfigTest.o: system/tests/sysConfigTest.cpp 
	${MKDIR} -p ${TESTDIR}/system/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/system/tests/sysConfigTest.o system/tests/sysConfigTest.cpp


${TESTDIR}/system/tests/sysConfigTestRun.o: system/tests/sysConfigTestRun.cpp 
	${MKDIR} -p ${TESTDIR}/system/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/system/tests/sysConfigTestRun.o system/tests/sysConfigTestRun.cpp


${OBJECTDIR}/ldap/account_nomain.o: ${OBJECTDIR}/ldap/account.o ldap/account.cpp 
	${MKDIR} -p ${OBJECTDIR}/ldap
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ldap/account.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/account_nomain.o ldap/account.cpp;\
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
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/attributes_nomain.o ldap/attributes.cpp;\
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
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/data_nomain.o ldap/data.cpp;\
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
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/dataset_nomain.o ldap/dataset.cpp;\
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
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/editableGroup_nomain.o ldap/editableGroup.cpp;\
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
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/group_nomain.o ldap/group.cpp;\
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
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/mailGroup_nomain.o ldap/mailGroup.cpp;\
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
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ldap/server_nomain.o ldap/server.cpp;\
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
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/process_nomain.o system/process.cpp;\
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
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/workDir_nomain.o system/workDir.cpp;\
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
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/config_nomain.o utils/config.cpp;\
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
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/container_nomain.o utils/container.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/utils/container.o ${OBJECTDIR}/utils/container_nomain.o;\
	fi

${OBJECTDIR}/utils/log_nomain.o: ${OBJECTDIR}/utils/log.o utils/log.cpp 
	${MKDIR} -p ${OBJECTDIR}/utils
	@NMOUTPUT=`${NM} ${OBJECTDIR}/utils/log.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -fPIC  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/log_nomain.o utils/log.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/utils/log.o ${OBJECTDIR}/utils/log_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f4 || true; \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f3 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/liblibadmintools.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
