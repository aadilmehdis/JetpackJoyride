#include "main.h"

#ifndef WATERBALL_H
#define WATERBALL_H


class WaterBall {
public:
    WaterBall() {}
    WaterBall(float x, float y);
    glm::vec3 position;

    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();

    float rotation;
    float radius;
    double dx;
    double dy;
    double gravity;
    bounding_box_t bbox;

private:
    VAO *ball;
    VAO *tip;

    // VAO *bound;
};

#endif // BALL_H
