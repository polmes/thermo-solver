CC = g++-6
CFLAGS = -std=c++14 -g -O3 -c -Wall -pedantic
LFLAGS = -std=c++14 -g
LIBS = -pthread

EXE = thermo

$(EXE): obj/main.o obj/mesh.o obj/volume.o obj/material.o obj/condition.o
	$(CC) $(LFLAGS) obj/*.o -o $(EXE) $(LIBS)

obj/main.o: main.cpp mesh.hpp condition.hpp util.hpp headers.hpp
	$(CC) $(CFLAGS) main.cpp -o obj/main.o $(LIBS)

obj/mesh.o: mesh.cpp mesh.hpp condition.hpp util.hpp headers.hpp
	$(CC) $(CFLAGS) mesh.cpp -o obj/mesh.o $(LIBS)

obj/volume.o: volume.cpp volume.hpp condition.hpp util.hpp headers.hpp
	$(CC) $(CFLAGS) volume.cpp -o obj/volume.o $(LIBS)

obj/material.o: material.cpp material.hpp headers.hpp
	$(CC) $(CFLAGS) material.cpp -o obj/material.o $(LIBS)

obj/condition.o: condition.cpp condition.hpp headers.hpp
	$(CC) $(CFLAGS) condition.cpp -o obj/condition.o $(LIBS)

clean:
	rm thermo obj/*
