EXE = assignment3
CC = g++

$(EXE): property.o house.o apartment_complex.o business_complex.o space.o tenant.o citizen.o business.o player.o game.o driver.o
	$(CC) property.o house.o apartment_complex.o business_complex.o space.o tenant.o citizen.o business.o player.o game.cpp driver.o -o $(EXE)
property.o: property.cpp
	$(CC) -c property.cpp
house.o: house.cpp
	$(CC) -c house.cpp
apartment_complex.o: apartment_complex.cpp
	$(CC) -c apartment_complex.cpp
business_complex.o: business_complex.cpp
	$(CC) -c business_complex.cpp
space.o: space.cpp
	$(CC) -c space.cpp
tenant.o: tenant.cpp
	$(CC) -c tenant.cpp
citizen.o: citizen.cpp
	$(CC) -c citizen.cpp
business.o: business.cpp
	$(CC) -c business.cpp
player.o: player.cpp
	$(CC) -c player.cpp
game.o: game.cpp
	$(CC) -c game.cpp
driver.o: driver.cpp
	$(CC) -c driver.cpp

clean:
	rm -f *.out *.o $(EXE)
