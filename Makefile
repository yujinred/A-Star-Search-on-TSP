CXX = g++
CXXFLAGS = -g -Wall -MMD
OBJECTS = TravellingSalesmen.o Node.o Tree.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = a.out

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY : clean
clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}