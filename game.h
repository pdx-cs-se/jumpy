#ifndef GAME_H
#define GAME_H

#include <random>

using namespace std;

// Frame rate in frames per second.
static const int FRAME_RATE = 30;

// Jump velocity in chars per frame.
static const float JUMP_VEL = 1.5;

// Jump deceleration in chars per frame per frame.
static const float JUMP_DECEL = 0.2;

// Initial floor movement rate in chars per frame.
static const float FLOOR_RATE = 0.2;

// Floor movement acceleration rate in chars per frame per frame.
static const float FLOOR_ACCEL = 0.002;

// PRNG.
extern default_random_engine generator;

#endif
