#ifndef FLOOR_H
#define FLOOR_H

#include <random>
#include <vector>

#include "game.h"

using namespace std;

class GameState;

class Floor {
    vector<char> tiles;
    float hole_prob = 0.01;

    static char floor_tile(void) {
        static string terrain = "#*O@";
        static uniform_int_distribution<int>
            distribution(0, terrain.length() - 1);
        int terrain_index = distribution(generator);
        return terrain[terrain_index];
    }

public:
    Floor();
    virtual void draw(void);
    virtual bool update(GameState &state);
    virtual bool on_space(void);
};

#endif
