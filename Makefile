CC = g++-6
CFLAGS = -std=c++14 -g -O3 -c -Wall -pedantic
LFLAGS = -std=c++14 -g
LIBS = -pthread

EXE = thermo

$(EXE): obj/main.o obj/mesh.o obj/volume.o
	$(CC) $(LFLAGS) obj/*.o -o $(EXE) $(LIBS)

obj/main.o: main.cpp mesh.hpp
	$(CC) $(CFLAGS) main.cpp -o obj/main.o $(LIBS)

obj/mesh.o: mesh.cpp mesh.hpp
	$(CC) $(CFLAGS) main.cpp -o obj/mesh.o $(LIBS)

obj/volume.o: volume.cpp volume.hpp
	$(CC) $(CFLAGS) volume.cpp -o obj/volume.o $(LIBS)

clean:
	rm obj/*
