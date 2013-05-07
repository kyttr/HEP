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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/e6_myClass.o \
	${OBJECTDIR}/e6_Class.o \
	${OBJECTDIR}/altgraphv2.o \
	${OBJECTDIR}/main_compileFiles.o \
	${OBJECTDIR}/e6_rootMacro1.o \
	${OBJECTDIR}/e6_v3_Class.o \
	${OBJECTDIR}/altgraph.o \
	${OBJECTDIR}/e6_rootMacro1vTree.o \
	${OBJECTDIR}/kaon+-p-pT-eta-phiv2.o \
	${OBJECTDIR}/kaon+-p-pT-eta-phi.o \
	${OBJECTDIR}/exercise1_4_boun_HEP.o \
	${OBJECTDIR}/kaon+-p-pT-eta-phivTree.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bounhep

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bounhep: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bounhep ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/e6_myClass.o: e6_myClass.C 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/e6_myClass.o e6_myClass.C

${OBJECTDIR}/e6_Class.o: e6_Class.C 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/e6_Class.o e6_Class.C

${OBJECTDIR}/altgraphv2.o: altgraphv2.C 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/altgraphv2.o altgraphv2.C

${OBJECTDIR}/main_compileFiles.o: main_compileFiles.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main_compileFiles.o main_compileFiles.cpp

${OBJECTDIR}/e6_rootMacro1.o: e6_rootMacro1.C 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/e6_rootMacro1.o e6_rootMacro1.C

${OBJECTDIR}/e6_v3_Class.o: e6_v3_Class.C 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/e6_v3_Class.o e6_v3_Class.C

${OBJECTDIR}/altgraph.o: altgraph.C 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/altgraph.o altgraph.C

${OBJECTDIR}/e6_rootMacro1vTree.o: e6_rootMacro1vTree.C 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/e6_rootMacro1vTree.o e6_rootMacro1vTree.C

${OBJECTDIR}/kaon+-p-pT-eta-phiv2.o: kaon+-p-pT-eta-phiv2.cc 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/kaon+-p-pT-eta-phiv2.o kaon+-p-pT-eta-phiv2.cc

${OBJECTDIR}/kaon+-p-pT-eta-phi.o: kaon+-p-pT-eta-phi.cc 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/kaon+-p-pT-eta-phi.o kaon+-p-pT-eta-phi.cc

${OBJECTDIR}/exercise1_4_boun_HEP.o: exercise1_4_boun_HEP.C 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/exercise1_4_boun_HEP.o exercise1_4_boun_HEP.C

${OBJECTDIR}/kaon+-p-pT-eta-phivTree.o: kaon+-p-pT-eta-phivTree.cc 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/kaon+-p-pT-eta-phivTree.o kaon+-p-pT-eta-phivTree.cc

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/bounhep

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
