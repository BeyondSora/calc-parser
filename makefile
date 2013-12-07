CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -MMD -I lib

OBJECTS = calc_parse.o parser_combinator/parser_combinator.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = calc

${EXEC} : ${OBJECTS}
		${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
		rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}
