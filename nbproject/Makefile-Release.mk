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
CND_PLATFORM=GNU-Linux
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
	${OBJECTDIR}/argument/argument.o \
	${OBJECTDIR}/command/command.o \
	${OBJECTDIR}/configuration/configuration.o \
	${OBJECTDIR}/error/error.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/service/repository.o \
	${OBJECTDIR}/service/service.o \
	${OBJECTDIR}/type/string.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f3 \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/configuration_cunit_test.o \
	${TESTDIR}/tests/repository_cunit_test.o \
	${TESTDIR}/tests/string_type_cunit_test.o

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
LDLIBSOPTIONS=`pkg-config --libs libcurl` `pkg-config --libs jansson`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/shill

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/shill: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/shill ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/argument/argument.o: argument/argument.c 
	${MKDIR} -p ${OBJECTDIR}/argument
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror `pkg-config --cflags libcurl` `pkg-config --cflags jansson` -std=c11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/argument/argument.o argument/argument.c

${OBJECTDIR}/command/command.o: command/command.c 
	${MKDIR} -p ${OBJECTDIR}/command
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror `pkg-config --cflags libcurl` `pkg-config --cflags jansson` -std=c11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/command/command.o command/command.c

${OBJECTDIR}/configuration/configuration.o: configuration/configuration.c 
	${MKDIR} -p ${OBJECTDIR}/configuration
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror `pkg-config --cflags libcurl` `pkg-config --cflags jansson` -std=c11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/configuration/configuration.o configuration/configuration.c

${OBJECTDIR}/error/error.o: error/error.c 
	${MKDIR} -p ${OBJECTDIR}/error
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror `pkg-config --cflags libcurl` `pkg-config --cflags jansson` -std=c11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/error/error.o error/error.c

${OBJECTDIR}/main.o: main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror `pkg-config --cflags libcurl` `pkg-config --cflags jansson` -std=c11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/service/repository.o: service/repository.c 
	${MKDIR} -p ${OBJECTDIR}/service
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror `pkg-config --cflags libcurl` `pkg-config --cflags jansson` -std=c11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/service/repository.o service/repository.c

${OBJECTDIR}/service/service.o: service/service.c 
	${MKDIR} -p ${OBJECTDIR}/service
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror `pkg-config --cflags libcurl` `pkg-config --cflags jansson` -std=c11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/service/service.o service/service.c

${OBJECTDIR}/type/string.o: type/string.c 
	${MKDIR} -p ${OBJECTDIR}/type
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror `pkg-config --cflags libcurl` `pkg-config --cflags jansson` -std=c11  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/type/string.o type/string.c

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f3: ${TESTDIR}/tests/configuration_cunit_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c}   -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS} -lcunit 

${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/repository_cunit_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c}   -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} -lcunit 

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/string_type_cunit_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} -lcunit 


${TESTDIR}/tests/configuration_cunit_test.o: tests/configuration_cunit_test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror `pkg-config --cflags libcurl` `pkg-config --cflags jansson` -std=c11  -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/configuration_cunit_test.o tests/configuration_cunit_test.c


${TESTDIR}/tests/repository_cunit_test.o: tests/repository_cunit_test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror `pkg-config --cflags libcurl` `pkg-config --cflags jansson` -std=c11  -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/repository_cunit_test.o tests/repository_cunit_test.c


${TESTDIR}/tests/string_type_cunit_test.o: tests/string_type_cunit_test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Werror `pkg-config --cflags libcurl` `pkg-config --cflags jansson` -std=c11  -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/string_type_cunit_test.o tests/string_type_cunit_test.c


${OBJECTDIR}/argument/argument_nomain.o: ${OBJECTDIR}/argument/argument.o argument/argument.c 
	${MKDIR} -p ${OBJECTDIR}/argument
	@NMOUTPUT=`${NM} ${OBJECTDIR}/argument/argument.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Werror `pkg-config --cflags libcurl` `pkg-config --cflags jansson` -std=c11  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/argument/argument_nomain.o argument/argument.c;\
	else  \
	    ${CP} ${OBJECTDIR}/argument/argument.o ${OBJECTDIR}/argument/argument_nomain.o;\
	fi

${OBJECTDIR}/command/command_nomain.o: ${OBJECTDIR}/command/command.o command/command.c 
	${MKDIR} -p ${OBJECTDIR}/command
	@NMOUTPUT=`${NM} ${OBJECTDIR}/command/command.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Werror `pkg-config --cflags libcurl` `pkg-config --cflags jansson` -std=c11  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/command/command_nomain.o command/command.c;\
	else  \
	    ${CP} ${OBJECTDIR}/command/command.o ${OBJECTDIR}/command/command_nomain.o;\
	fi

${OBJECTDIR}/configuration/configuration_nomain.o: ${OBJECTDIR}/configuration/configuration.o configuration/configuration.c 
	${MKDIR} -p ${OBJECTDIR}/configuration
	@NMOUTPUT=`${NM} ${OBJECTDIR}/configuration/configuration.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Werror `pkg-config --cflags libcurl` `pkg-config --cflags jansson` -std=c11  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/configuration/configuration_nomain.o configuration/configuration.c;\
	else  \
	    ${CP} ${OBJECTDIR}/configuration/configuration.o ${OBJECTDIR}/configuration/configuration_nomain.o;\
	fi

${OBJECTDIR}/error/error_nomain.o: ${OBJECTDIR}/error/error.o error/error.c 
	${MKDIR} -p ${OBJECTDIR}/error
	@NMOUTPUT=`${NM} ${OBJECTDIR}/error/error.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Werror `pkg-config --cflags libcurl` `pkg-config --cflags jansson` -std=c11  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/error/error_nomain.o error/error.c;\
	else  \
	    ${CP} ${OBJECTDIR}/error/error.o ${OBJECTDIR}/error/error_nomain.o;\
	fi

${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Werror `pkg-config --cflags libcurl` `pkg-config --cflags jansson` -std=c11  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main_nomain.o main.c;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

${OBJECTDIR}/service/repository_nomain.o: ${OBJECTDIR}/service/repository.o service/repository.c 
	${MKDIR} -p ${OBJECTDIR}/service
	@NMOUTPUT=`${NM} ${OBJECTDIR}/service/repository.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Werror `pkg-config --cflags libcurl` `pkg-config --cflags jansson` -std=c11  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/service/repository_nomain.o service/repository.c;\
	else  \
	    ${CP} ${OBJECTDIR}/service/repository.o ${OBJECTDIR}/service/repository_nomain.o;\
	fi

${OBJECTDIR}/service/service_nomain.o: ${OBJECTDIR}/service/service.o service/service.c 
	${MKDIR} -p ${OBJECTDIR}/service
	@NMOUTPUT=`${NM} ${OBJECTDIR}/service/service.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Werror `pkg-config --cflags libcurl` `pkg-config --cflags jansson` -std=c11  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/service/service_nomain.o service/service.c;\
	else  \
	    ${CP} ${OBJECTDIR}/service/service.o ${OBJECTDIR}/service/service_nomain.o;\
	fi

${OBJECTDIR}/type/string_nomain.o: ${OBJECTDIR}/type/string.o type/string.c 
	${MKDIR} -p ${OBJECTDIR}/type
	@NMOUTPUT=`${NM} ${OBJECTDIR}/type/string.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -O2 -Werror `pkg-config --cflags libcurl` `pkg-config --cflags jansson` -std=c11  -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/type/string_nomain.o type/string.c;\
	else  \
	    ${CP} ${OBJECTDIR}/type/string.o ${OBJECTDIR}/type/string_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f3 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/shill

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
