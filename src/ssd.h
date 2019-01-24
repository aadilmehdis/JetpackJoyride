#include "main.h"

#ifndef SSD_H
#define SSD_H


class SSD {
public:
    SSD() {}
    SSD(float x, float y, color_t color );
    glm::vec3 position;

    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void set_digit(int dig);
    void tick();

    float rotation;
    double dx;
    double dy;
    double gravity;
    int digit;

private:
    VAO *a;
    VAO *b;
    VAO *c;
    VAO *d;
    VAO *e;
    VAO *f;
    VAO *g;
};

#endif // BALL_H
