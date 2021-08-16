all: semA semB
semA:sem.hpp
	g++ semA.cpp -o semA

semB:sem.hpp
	g++ semB.cpp -o semB

clean:
	rm semA
	rm semB
	ipcrm -a