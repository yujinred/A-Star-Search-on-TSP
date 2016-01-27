# Universal makefile for multiple C++ programs
#
# Use gcc flag -MMD (user) or -MD (user/system) to generate dependences among source files.
# Use make default rules for commonly used file-name suffixes and make variables names.
#
# % make [ searcher | phil ]

########## Variables ##########

CXX = g++					
CXXFLAGS = -g -std=c++11 -Wall -MMD	
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}

OBJECTS1 = UserInterface.o Search.o Tree.o Node.o Heuristics.o			
EXEC1 = ui				

OBJECTS2 = GenerateData.o Search.o Tree.o Node.o Heuristics.o					
EXEC2 = data				

OBJECTS = ${OBJECTS1} ${OBJECTS2}	
DEPENDS = ${OBJECTS:.o=.d}		
EXECS = ${EXEC1} ${EXEC2}		

########## Targets ##########

.PHONY : all clean				# not file names

all : ${EXECS}					# build all executables

${EXEC1} : ${OBJECTS1}				# link step 1st executable
	${CXX} ${CXXFLAGS} $^ -o $@		# additional object files before $^

${EXEC2} : ${OBJECTS2}				# link step 2nd executable
	${CXX} ${CXXFLAGS} $^ -o $@		# additional object files before $^

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f ${DEPENDS} ${OBJECTS} ${EXECS}