## Makefile for Jumpy — Side-scrolling runner / platformer

CXX = g++
CXXFLAGS = -Wall -Werror -g

OBJS = game.o floor.o jumpy.o gamestate.o

jumpy: $(OBJS)
	$(CXX) $(CXXFLAGS) -o jumpy $(OBJS) -lncurses

game.o: game.h jumpy.h floor.h gamestate.h

floor.o: game.h floor.h gamestate.h

jumpy.o: game.h jumpy.h gamestate.h

gamestate.o: jumpy.h floor.h gamestate.h

clean:
	-rm -f $(OBJS) jumpy
