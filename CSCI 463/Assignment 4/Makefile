Assign4: main.cpp memory.cpp hex.cpp rv32i_decode.cpp memory.h hex.h rv32i_decode.h
	g++ -g -ansi -pedantic -Wall -Werror -Wextra -std=c++14 -c -o main.o main.cpp
	g++ -g -ansi -pedantic -Wall -Werror -Wextra -std=c++14 -c -o memory.o memory.cpp
	g++ -g -ansi -pedantic -Wall -Werror -Wextra -std=c++14 -c -o hex.o hex.cpp
	g++ -g -Wno-unused -ansi -pedantic -Wall -Werror -Wextra -std=c++14 -c -o rv32i_decode.o rv32i_decode.cpp
	g++ -g -ansi -pedantic -Wall -Werror -Wextra -std=c++14 -o rv32i main.o memory.o hex.o rv32i_decode.o
clean:
	rm *.exe
