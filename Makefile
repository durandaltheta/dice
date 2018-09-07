cc=g++
wccc=x86_64-w64-mingw32-g++
flags=-Wall -Wextra -Werror

ifeq ($(OS),Windows_NT)
win-only: win
else
all: lin win-cross
endif


lin: dice.cpp
	$(cc) $(flags) dice.cpp -o dice

win: dice.cpp
	$(cc) $(flags) dice.cpp -o dice.exe

win-cross: dice.cpp $(wildcard not-win)
	$(wccc) $(flags) dice.cpp -o dice.exe

clean:
	rm dice dice.exe
