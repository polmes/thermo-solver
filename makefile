CC = g++-6
CFLAGS = -std=c++14 -g -O3 -c -Wall -pedantic
LFLAGS = -std=c++14 -g
# Might want to add LIBS = -pthread, etc. in the future

EXE = thermo

$(EXE): obj/main.o obj/mesh.o obj/volume.o
	$(CC) $(LFLAGS) obj/*.o -o $(EXE)

obj/main.o: main.cpp mesh.hpp
	$(CC) $(CFLAGS) main.cpp -o obj/main.o

obj/mesh.o: mesh.cpp mesh.hpp
	$(CC) $(CFLAGS) main.cpp -o obj/mesh.o

obj/volume.o: volume.cpp volume.hpp
	$(CC) $(CFLAGS) volume.cpp -o obj/volume.o

clean:
	rm obj/*
