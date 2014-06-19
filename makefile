UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)

all:
	gcc *.c -g -I/Library/Frameworks/SDL_image.framework/Headers -I/Library/Frameworks/SDL_ttf.framework/Headers -I/Library/Frameworks/SDL.framework/Headers -framework SDL -framework Cocoa -lm -framework SDL_image -framework SDL_ttf -Wunused-variable *.m -o KPSpamRunner

else

all:
	gcc -I/usr/include/SDL *.c -g -lSDL -lm -lSDL_image  -lSDL_ttf -Wunused-variable -o KPSpamRunner

endif


