# LDFLAGS = `pkg-config --static --libs glfw3` -lglad
LDFLAGS = -lglfw -lglad
CC=g++
CFLAGS=-std=c++14
OBJS = main.cpp solid.cpp platonic_solid.cpp uv_sphere.cpp icosahedron.cpp face.cpp
OBJ_NAME = solids

solids: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(OBJ_NAME)
	./$(OBJ_NAME)

clean:
	if [ -f $(OBJ_NAME) ]; then rm $(OBJ_NAME); fi;

test: clean $(OBJ_NAME)
	./$(OBJ_NAME)

run: ./$(OBJ_NAME)
