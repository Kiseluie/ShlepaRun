#OBJS specifies which files to compile as part of the project
OBJS = main.cpp Texture.hpp Texture.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main

DIRS = -I./src/

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(DIRS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	cat ./Makefile
