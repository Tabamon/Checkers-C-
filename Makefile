all: checkers

checkers: main.o boardClass.o squareClass.o
	clang++ -Wall -Wextra -Wpedantic main.o boardClass.o squareClass.o -o checkers

main.o: main.cpp
	clang++ -c -Wall -Wextra -Wpedantic main.cpp

boardClass.o: boardClass.cpp
	clang++ -c -Wall -Wextra -Wpedantic boardClass.cpp

squareClass.o: squareClass.cpp
	clang++ -c -Wall -Wextra -Wpedantic squareClass.cpp

clear:
	rm -rf *o