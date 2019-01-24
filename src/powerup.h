#include "main.h"

#ifndef POWERUP_H
#define POWERUP_H


class PowerUp {
public:
    PowerUp() {}
    PowerUp(float x, float y, color_t color, int type);
    glm::vec3 position;

    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();

    float rotation;
    float radius;
    double dx;
    double dy;
    double gravity;
    double oscillator;
    int type;
    bounding_box_t bbox;

private:
    VAO *coin;
    VAO *life_boost;
    VAO *immune_boost;
    VAO *magnet_boost;
};

#endif // BALL_H
