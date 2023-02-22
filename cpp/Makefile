#OBJS specifies which files to compile as part of the project
OBJS = ./src/main.cpp \
	   ./src/Texture.hpp \
	   ./src/Texture.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main

BUILD_DIR = ./build

#This is the target that compiles our executable
all : $(OBJS)
	make -s clean-all
	make -s copy-media
	make -s compilation

clean-all : 
	echo "Начато удаление каталога build"
	[ -d $(BUILD_DIR) ] && rm -R $(BUILD_DIR)
	echo "Каталог build удалён.\n"

copy-media:
	echo "Начато копирование медиа файлов"
	cp -R ./media $(BUILD_DIR)
	echo "Копирование медиа файлов завершино\n"

compilation:
	echo "Начато компилирование программы"
	$(CC) $(OBJS) $(DIRS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(BUILD_DIR)/$(OBJ_NAME)
	echo "Компилирование завершено\n"
