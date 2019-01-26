#include "main.h"

#ifndef SemiCircularRing_H
#define SemiCircularRing_H


class SemiCircularRing {
public:
    SemiCircularRing() {}
    SemiCircularRing(float x, float y);
    glm::vec3 position;

    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();

    float rotation;
    float radius;
    float radius_inner;
    float center_x;
    float center_y;
    bool entered;
    double dx;
    double dy;
    double gravity;
    bounding_box_t bbox;

private:
    VAO *ball;
    VAO *innerball;
};

#endif // BALL_H
