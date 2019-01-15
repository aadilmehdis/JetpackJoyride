#include "main.h"

#ifndef FIRELINE_H
#define FIRELINE_H


class FireLine {
public:
    FireLine() {}
    FireLine(float x, float y, color_t color );
    glm::vec3 position;

    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();

    float rotation;
    double dx;
    double dy;
    double gravity;

private:
    VAO *object;
};

#endif // BALL_H
