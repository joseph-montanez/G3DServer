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
	${OBJECTDIR}/admin/layout.o \
	${OBJECTDIR}/admin/blog/posts.o \
	${OBJECTDIR}/index.o \
	${OBJECTDIR}/admin/dashboard.o \
	${OBJECTDIR}/admin/index.o \
	${OBJECTDIR}/admin/blog/comments.o \
	${OBJECTDIR}/blog/layout.o \
	${OBJECTDIR}/admin/logout.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/admin/login.o

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
LDLIBSOPTIONS=../webserver/dist/Release/GNU-Linux-x86/webserver -lpthread -ldl -lsqlite3

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/Cygwin-Windows/website.exe

dist/Release/Cygwin-Windows/website.exe: ../webserver/dist/Release/GNU-Linux-x86/webserver

dist/Release/Cygwin-Windows/website.exe: ${OBJECTFILES}
	${MKDIR} -p dist/Release/Cygwin-Windows
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/website -s ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/admin/layout.o: nbproject/Makefile-${CND_CONF}.mk admin/layout.cpp 
	${MKDIR} -p ${OBJECTDIR}/admin
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/admin/layout.o admin/layout.cpp

${OBJECTDIR}/admin/blog/posts.o: nbproject/Makefile-${CND_CONF}.mk admin/blog/posts.cpp 
	${MKDIR} -p ${OBJECTDIR}/admin/blog
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/admin/blog/posts.o admin/blog/posts.cpp

${OBJECTDIR}/index.o: nbproject/Makefile-${CND_CONF}.mk index.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/index.o index.cpp

${OBJECTDIR}/admin/dashboard.o: nbproject/Makefile-${CND_CONF}.mk admin/dashboard.cpp 
	${MKDIR} -p ${OBJECTDIR}/admin
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/admin/dashboard.o admin/dashboard.cpp

${OBJECTDIR}/admin/index.o: nbproject/Makefile-${CND_CONF}.mk admin/index.cpp 
	${MKDIR} -p ${OBJECTDIR}/admin
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/admin/index.o admin/index.cpp

${OBJECTDIR}/admin/blog/comments.o: nbproject/Makefile-${CND_CONF}.mk admin/blog/comments.cpp 
	${MKDIR} -p ${OBJECTDIR}/admin/blog
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/admin/blog/comments.o admin/blog/comments.cpp

${OBJECTDIR}/blog/layout.o: nbproject/Makefile-${CND_CONF}.mk blog/layout.cpp 
	${MKDIR} -p ${OBJECTDIR}/blog
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/blog/layout.o blog/layout.cpp

${OBJECTDIR}/admin/logout.o: nbproject/Makefile-${CND_CONF}.mk admin/logout.cpp 
	${MKDIR} -p ${OBJECTDIR}/admin
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/admin/logout.o admin/logout.cpp

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/admin/login.o: nbproject/Makefile-${CND_CONF}.mk admin/login.cpp 
	${MKDIR} -p ${OBJECTDIR}/admin
	${RM} $@.d
	$(COMPILE.cc) -O2 -Wall -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/admin/login.o admin/login.cpp

# Subprojects
.build-subprojects:
	cd ../webserver && ${MAKE}  -f Makefile CONF=Release

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} dist/Release/Cygwin-Windows/website.exe

# Subprojects
.clean-subprojects:
	cd ../webserver && ${MAKE}  -f Makefile CONF=Release clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
