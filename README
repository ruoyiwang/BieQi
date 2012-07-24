CXX = g++ 			
CXXFLAGS = -Wall -O -g `pkg-config gtkmm-2.4 --cflags` -MMD
LDFLAGS=`pkg-config gtkmm-2.4 --libs`
OBJECTS = Card.o Command.o main.o Player.o Referee.o Table.o view.o DeckGUI.o Controller.o Subject.o Model.o PlayerBox.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} $(LDFLAGS) -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}	# reads the .d files and reruns dependencies