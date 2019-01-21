#include "main.h"

#ifndef DRAGON_H
#define DRAGON_H


class Dragon {
public:
    Dragon() {}
    Dragon(float x, float y, color_t color );
    glm::vec3 position;

    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();

    float rotation;
    float oscillator;
    double dx;
    double dy;
    double gravity;

private:
    VAO *object;
    VAO *ears;
    VAO *eyes;
    VAO *lin;
};

#endif // BALL_H
