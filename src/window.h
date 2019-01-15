#include "main.h"

#ifndef WINDOW_H
#define WINDOW_H


class Window {
public:
    Window() {}
    Window(float x, float y, color_t color );
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
