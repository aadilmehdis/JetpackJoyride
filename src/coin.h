#include "main.h"

#ifndef COIN_H
#define COIN_H


class Coin {
public:
    Coin() {}
    Coin(float x, float y, color_t color, bool special);
    glm::vec3 position;

    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();

    float rotation;
    float radius;
    double dx;
    double dy;
    double gravity;
    bool special_coin;
    bounding_box_t bbox;

private:
    VAO *object;
    // VAO *bound;
};

#endif // BALL_H
