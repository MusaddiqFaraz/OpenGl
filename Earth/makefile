CC=g++
CFLAGS=-lfreeglut -lSOIL -lglu32 -lopengl32
DEPS = SpaceBox.h 
OBJ = EarthMoon.o Planet.o SpaceBox.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Earth: $(OBJ)
	g++ -o $@ $^ $(CFLAGS)