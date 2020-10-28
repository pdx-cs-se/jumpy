## Makefile for Jumpy — Side-scrolling runner / platformer

CXX = g++
CXXFLAGS = -Wall -Werror -g

jumpy: jumpy.o
	$(CXX) $(CXXFLAGS) -o jumpy jumpy.o -lncurses

clean:
	-rm -f *.o jumpy
