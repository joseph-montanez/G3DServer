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
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=gfortran.exe
AS=as.exe

# Macros
CND_PLATFORM=Cygwin-Windows
CND_CONF=Release
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/WebString.o \
	${OBJECTDIR}/WebCookie.o \
	${OBJECTDIR}/WebRequest.o \
	${OBJECTDIR}/Socket.o \
	${OBJECTDIR}/WebResponse.o \
	${OBJECTDIR}/WebServer.o \
	${OBJECTDIR}/WebSession.o \
	${OBJECTDIR}/WebController.o \
	${OBJECTDIR}/ServerSocket.o \
	${OBJECTDIR}/SqlQuery.o \
	${OBJECTDIR}/SqlRow.o

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
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/Cygwin-Windows/libwebserver.a

dist/Release/Cygwin-Windows/libwebserver.a: ${OBJECTFILES}
	${MKDIR} -p dist/Release/Cygwin-Windows
	${RM} dist/Release/Cygwin-Windows/libwebserver.a
	${AR} rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libwebserver.a ${OBJECTFILES} 
	$(RANLIB) dist/Release/Cygwin-Windows/libwebserver.a

${OBJECTDIR}/WebString.o: nbproject/Makefile-${CND_CONF}.mk WebString.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/WebString.o WebString.cpp

${OBJECTDIR}/WebCookie.o: nbproject/Makefile-${CND_CONF}.mk WebCookie.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/WebCookie.o WebCookie.cpp

${OBJECTDIR}/WebRequest.o: nbproject/Makefile-${CND_CONF}.mk WebRequest.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/WebRequest.o WebRequest.cpp

${OBJECTDIR}/Socket.o: nbproject/Makefile-${CND_CONF}.mk Socket.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/Socket.o Socket.cpp

${OBJECTDIR}/WebResponse.o: nbproject/Makefile-${CND_CONF}.mk WebResponse.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/WebResponse.o WebResponse.cpp

${OBJECTDIR}/WebServer.o: nbproject/Makefile-${CND_CONF}.mk WebServer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/WebServer.o WebServer.cpp

${OBJECTDIR}/WebSession.o: nbproject/Makefile-${CND_CONF}.mk WebSession.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/WebSession.o WebSession.cpp

${OBJECTDIR}/WebController.o: nbproject/Makefile-${CND_CONF}.mk WebController.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/WebController.o WebController.cpp

${OBJECTDIR}/ServerSocket.o: nbproject/Makefile-${CND_CONF}.mk ServerSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/ServerSocket.o ServerSocket.cpp

${OBJECTDIR}/SqlQuery.o: nbproject/Makefile-${CND_CONF}.mk SqlQuery.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/SqlQuery.o SqlQuery.cpp

${OBJECTDIR}/SqlRow.o: nbproject/Makefile-${CND_CONF}.mk SqlRow.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/SqlRow.o SqlRow.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} dist/Release/Cygwin-Windows/libwebserver.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
