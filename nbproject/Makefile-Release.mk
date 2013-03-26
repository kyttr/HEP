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
	${OBJECTDIR}/_ext/1965768066/altgraphv2.o \
	${OBJECTDIR}/_ext/1965768066/kaon+-p-pT-eta-phi.o \
	${OBJECTDIR}/_ext/1965768066/exercise1_4_boun_HEP.o \
	${OBJECTDIR}/_ext/1965768066/altgraph.o \
	${OBJECTDIR}/kaon+-p-pT-eta-phiv2.o \
	${OBJECTDIR}/_ext/1965768066/main_compileFiles.o


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

${OBJECTDIR}/_ext/1965768066/altgraphv2.o: /home/kaya/Documents/particle-physics-kaya/bounHEP/altgraphv2.C 
	${MKDIR} -p ${OBJECTDIR}/_ext/1965768066
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1965768066/altgraphv2.o /home/kaya/Documents/particle-physics-kaya/bounHEP/altgraphv2.C

${OBJECTDIR}/_ext/1965768066/kaon+-p-pT-eta-phi.o: /home/kaya/Documents/particle-physics-kaya/bounHEP/kaon+-p-pT-eta-phi.cc 
	${MKDIR} -p ${OBJECTDIR}/_ext/1965768066
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1965768066/kaon+-p-pT-eta-phi.o /home/kaya/Documents/particle-physics-kaya/bounHEP/kaon+-p-pT-eta-phi.cc

${OBJECTDIR}/_ext/1965768066/exercise1_4_boun_HEP.o: /home/kaya/Documents/particle-physics-kaya/bounHEP/exercise1_4_boun_HEP.C 
	${MKDIR} -p ${OBJECTDIR}/_ext/1965768066
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1965768066/exercise1_4_boun_HEP.o /home/kaya/Documents/particle-physics-kaya/bounHEP/exercise1_4_boun_HEP.C

${OBJECTDIR}/_ext/1965768066/altgraph.o: /home/kaya/Documents/particle-physics-kaya/bounHEP/altgraph.C 
	${MKDIR} -p ${OBJECTDIR}/_ext/1965768066
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1965768066/altgraph.o /home/kaya/Documents/particle-physics-kaya/bounHEP/altgraph.C

${OBJECTDIR}/kaon+-p-pT-eta-phiv2.o: kaon+-p-pT-eta-phiv2.cc 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/kaon+-p-pT-eta-phiv2.o kaon+-p-pT-eta-phiv2.cc

${OBJECTDIR}/_ext/1965768066/main_compileFiles.o: /home/kaya/Documents/particle-physics-kaya/bounHEP/main_compileFiles.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1965768066
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1965768066/main_compileFiles.o /home/kaya/Documents/particle-physics-kaya/bounHEP/main_compileFiles.cpp

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
