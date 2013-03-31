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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/altgraphv2.o \
	${OBJECTDIR}/altgraph.o \
	${OBJECTDIR}/kaon+-p-pT-eta-phiv2.o \
	${OBJECTDIR}/kaon+-p-pT-eta-phi.o \
	${OBJECTDIR}/exercise1_4_boun_HEP.o \
	${OBJECTDIR}/kaon+-p-pT-eta-phivTree.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=`root-config --cflags --libs` 
CXXFLAGS=`root-config --cflags --libs` 

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

${OBJECTDIR}/altgraphv2.o: altgraphv2.C 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../PYTHIA/pythia8175/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/altgraphv2.o altgraphv2.C

${OBJECTDIR}/altgraph.o: altgraph.C 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../PYTHIA/pythia8175/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/altgraph.o altgraph.C

${OBJECTDIR}/kaon+-p-pT-eta-phiv2.o: kaon+-p-pT-eta-phiv2.cc 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../PYTHIA/pythia8175/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/kaon+-p-pT-eta-phiv2.o kaon+-p-pT-eta-phiv2.cc

${OBJECTDIR}/kaon+-p-pT-eta-phi.o: kaon+-p-pT-eta-phi.cc 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../PYTHIA/pythia8175/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/kaon+-p-pT-eta-phi.o kaon+-p-pT-eta-phi.cc

${OBJECTDIR}/exercise1_4_boun_HEP.o: exercise1_4_boun_HEP.C 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../PYTHIA/pythia8175/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/exercise1_4_boun_HEP.o exercise1_4_boun_HEP.C

${OBJECTDIR}/kaon+-p-pT-eta-phivTree.o: kaon+-p-pT-eta-phivTree.cc 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../PYTHIA/pythia8175/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/kaon+-p-pT-eta-phivTree.o kaon+-p-pT-eta-phivTree.cc

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
