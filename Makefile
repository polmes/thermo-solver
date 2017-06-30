CC = g++-6
CFLAGS = -std=c++14 -g -O3 -c -Wall -pedantic
LFLAGS = -std=c++14 -g
LIBS = -pthread

EXE = thermo

$(EXE): obj/*.o
	$(CC) $(LFLAGS) obj/*.o -o $(EXE) $(LIBS)

obj/main.o: main.cpp mesh.hpp
	$(CC) $(CFLAGS) main.cpp -o obj/main.o $(LIBS)

obj/mesh.o: mesh.cpp mesh.hpp
	$(CC) $(CFLAGS) main.cpp -o obj/mesh.o $(LIBS)

obj/material.o: material.cpp materia.hpp
	$(CC) $(CFLAGS) material.cpp -o obj/material.o $(LIBS)

obj/volume.o: volume.cpp volume.hpp
	$(CC) $(CFLAGS) volume.cpp -o obj/volume.o $(LIBS)

obj/util.o: util.cpp
	$(CC) $(CFLAGS) util.cpp -o obj/util.o $(LIBS)

clean:
	rm obj/*
