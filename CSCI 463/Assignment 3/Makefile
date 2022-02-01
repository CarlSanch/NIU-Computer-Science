memsim: main.o memory.o hex.o
	g++ -pedantic -Wall -Werror -Wextra -g -std=c++11 -o memsim main.o memory.o hex.o
main.o: main.cpp hex.h memory.h
	g++ -pedantic -Wall -Werror -Wextra -g -std=c++11 -c main.cpp
memory.o: memory.cpp memory.h
	g++ -pedantic -Wall -Werror -Wextra -g -std=c++11 -c memory.cpp
hex.o: hex.cpp hex.h
	g++ -pedantic -Wall -Werror -Wextra -g -std=c++11 -c hex.cpp

clean:
	rm -f *.o main
