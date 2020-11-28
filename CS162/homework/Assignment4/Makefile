EXE = assignment4
CC = g++

$(EXE): insect.o bee.o ant.o harvester.o long_thrower.o short_thrower.o thrower.o fire.o wall.o bodyguard.o ninja.o game.o driver.o
	$(CC) insect.o bee.o ant.o harvester.o long_thrower.o short_thrower.o thrower.o fire.o wall.o bodyguard.o ninja.o game.o driver.o -o $(EXE)
insect.o: insect.cpp
	$(CC) -c insect.cpp
bee.o: bee.cpp
	$(CC) -c bee.cpp
ant.o: ant.cpp
	$(CC) -c ant.cpp
harvester.o: harvester.cpp
	$(CC) -c harvester.cpp
long_thrower.o: long_thrower.cpp
	$(CC) -c long_thrower.cpp
short_thrower.o: short_thrower.cpp
	$(CC) -c short_thrower.cpp
thrower.o: thrower.cpp
	$(CC) -c thrower.cpp
fire.o: fire.cpp
	$(CC) -c fire.cpp
wall.o: wall.cpp
	$(CC) -c wall.cpp
bodyguard.o: bodyguard.cpp
	$(CC) -c bodyguard.cpp
ninja.o: ninja.cpp
	$(CC) -c ninja.cpp
game.o: game.cpp
	$(CC) -c game.cpp
driver.o: driver.cpp
	$(CC) -c driver.cpp

clean:
	rm -f *.out *.o $(EXE)
