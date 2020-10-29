#ifndef JUMPY_H
#define JUMPY_H

class GameState;

class Jumpy {
    // Jumpy's current y velocity.
    float vel_y = 0.0;
    // Jumpy's current y position.
    float pos_y = 1.0;
    char shape[3] = { '\\', 'M', 'O' };

public:
    // XXX Jumpy should be drawn last so that the cursor
    // ends up over their body.
    virtual void draw(void);

    // Returns true on game over.
    virtual bool update(GameState &state);
    virtual void jump(void);
};

#endif
