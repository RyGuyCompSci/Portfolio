INCLUDE_SFML= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -I/usr/include/SFML
CC=g++

CFLAGS= -Wall -g -std=c++11

OPTS = -I"./source/irrKlang-64bit-1.6.0/include" -L"/usr/lib" ./source/irrKlang-64bit-1.6.0/bin/linux-gcc-64/libIrrKlang.so -pthread

ENGINE_FILES =  ./source/GameEngine.cpp ./source/Scene.cpp ./source/View.cpp ./source/Object.cpp ./source/Sprite.cpp ./source/Globals.cpp ./source/HitBox.cpp

#GAME_FILES = ./your_game_file.cpp ./your_scene_file.cpp ./your_object_file.cpp $(ENGINE_FILES)
GAME_FILES = ./source/GameJam/Game.cpp ./source/GameJam/Scenes.cpp ./source/GameJam/Objects.cpp $(ENGINE_FILES)

parallel: ./source/GameJam/Game.cpp
	$(CC) $(CFLAGS) $(GAME_FILES) $(INCLUDE_SFML) $(OPTS) -o parallel

clean:
	rm -rf #your executables here
