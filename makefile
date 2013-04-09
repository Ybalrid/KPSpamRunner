all:
	gcc *.c -g -lSDL -lm -lSDL_image -lSDL_ttf -Wunused-variable -o KPSpamRunner
