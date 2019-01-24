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
    line_t get_position();
    void tick();

    float t_x;
    float t_y;

    float rotation;
    double dx;
    double dy;
    double gravity;
    bool danger;
    line_t line_coords;

private:
    VAO *circle1;
    VAO *circle2;
    VAO *line1;
    VAO *line2;
};

#endif // BALL_H
