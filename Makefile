cc=g++
wccc=x86_64-w64-mingw32-g++
flags=-Wall -Wextra -Werror

ifeq ($(OS),Windows_NT)
name=dice.exe
else
name=dice
endif


default: dice.cpp
	$(cc) $(flags) dice.cpp -o $(name)

win-cross: dice.cpp $(wildcard not-win)
	$(wccc) $(flags) dice.cpp -o $(name).exe

clean:
	rm $(name)
