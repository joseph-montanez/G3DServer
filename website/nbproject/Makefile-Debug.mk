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
FC=
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/admin/login.o \
	${OBJECTDIR}/admin/blog/comments.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/index.o \
	${OBJECTDIR}/admin/layout.o \
	${OBJECTDIR}/admin/logout.o \
	${OBJECTDIR}/admin/index.o \
	${OBJECTDIR}/blog/layout.o \
	${OBJECTDIR}/admin/blog/posts.o \
	${OBJECTDIR}/admin/dashboard.o


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
LDLIBSOPTIONS=../webserver/dist/Debug/GNU-Linux-x86/libwebserver.a -lpthread -lsqlite3

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/GNU-Linux-x86/website

dist/Debug/GNU-Linux-x86/website: ../webserver/dist/Debug/GNU-Linux-x86/libwebserver.a

dist/Debug/GNU-Linux-x86/website: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/website ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/admin/login.o: nbproject/Makefile-${CND_CONF}.mk admin/login.cpp 
	${MKDIR} -p ${OBJECTDIR}/admin
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/admin/login.o admin/login.cpp

${OBJECTDIR}/admin/blog/comments.o: nbproject/Makefile-${CND_CONF}.mk admin/blog/comments.cpp 
	${MKDIR} -p ${OBJECTDIR}/admin/blog
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/admin/blog/comments.o admin/blog/comments.cpp

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/index.o: nbproject/Makefile-${CND_CONF}.mk index.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/index.o index.cpp

${OBJECTDIR}/admin/layout.o: nbproject/Makefile-${CND_CONF}.mk admin/layout.cpp 
	${MKDIR} -p ${OBJECTDIR}/admin
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/admin/layout.o admin/layout.cpp

${OBJECTDIR}/admin/logout.o: nbproject/Makefile-${CND_CONF}.mk admin/logout.cpp 
	${MKDIR} -p ${OBJECTDIR}/admin
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/admin/logout.o admin/logout.cpp

${OBJECTDIR}/admin/index.o: nbproject/Makefile-${CND_CONF}.mk admin/index.cpp 
	${MKDIR} -p ${OBJECTDIR}/admin
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/admin/index.o admin/index.cpp

${OBJECTDIR}/blog/layout.o: nbproject/Makefile-${CND_CONF}.mk blog/layout.cpp 
	${MKDIR} -p ${OBJECTDIR}/blog
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/blog/layout.o blog/layout.cpp

${OBJECTDIR}/admin/blog/posts.o: nbproject/Makefile-${CND_CONF}.mk admin/blog/posts.cpp 
	${MKDIR} -p ${OBJECTDIR}/admin/blog
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/admin/blog/posts.o admin/blog/posts.cpp

${OBJECTDIR}/admin/dashboard.o: nbproject/Makefile-${CND_CONF}.mk admin/dashboard.cpp 
	${MKDIR} -p ${OBJECTDIR}/admin
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/admin/dashboard.o admin/dashboard.cpp

# Subprojects
.build-subprojects:
	cd ../webserver && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/website

# Subprojects
.clean-subprojects:
	cd ../webserver && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
