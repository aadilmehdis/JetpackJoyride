#include "main.h"

#ifndef ICEBALL_H
#define ICEBALL_H


class IceBall {
public:
    IceBall() {}
    IceBall(float x, float y);
    glm::vec3 position;

    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();

    float rotation;
    double dx;
    double dy;
    double gravity;
    bounding_box_t bbox;

private:
    VAO *ball;
};

#endif // BALL_H
