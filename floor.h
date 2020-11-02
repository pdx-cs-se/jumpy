#ifndef FLOOR_H
#define FLOOR_H

#include <random>
#include <vector>

#include "game.h"

using namespace std;

class GameState;

class Floor {
    // List of possible floor tile characters.
    vector<char> tiles;

    // Probability of a hole tile in the floor.
    float hole_prob = 0.01;

    // Rate at which floor shifts left.
    float floor_rate = FLOOR_RATE;

    // Accumulated unused floor shift.
    float floor_shift = 0.0;

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
