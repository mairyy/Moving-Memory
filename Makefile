all:
	g++ -Isrc/include/SDL2 -Lsrc/lib -o main main.cpp common.cpp pictures.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf