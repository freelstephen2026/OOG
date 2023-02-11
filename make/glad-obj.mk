CC=g++
SRC=/usr/local/src/glad.c
OBJ=build/obj/glad.o
LIBS=-lGL -lGLFW3

all: $(OBJ) $(SRC)

$(OBJ): $(SRC)
	$(CC) -o $@ -c $^ $(LIBS)