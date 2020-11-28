CC = g++
exeFile = lab1
$(exeFile): multDiv.o lab1.o
	$(CC) multDiv.o lab1.o -o $(exeFile)
multDiv.o: multDiv.cpp
	$(CC) -c multDiv.cpp
lab1.o: lab1.cpp
	$(CC) -c lab1.cpp

clean:
	rm -f *.out *.o $(exeFile)
