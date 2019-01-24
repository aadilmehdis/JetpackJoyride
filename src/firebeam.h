#include "main.h"

#ifndef FIREBEAM_H
#define FIREBEAM_H


class FireBeam {
public:
    FireBeam() {}
    FireBeam(float x, float y, color_t color );
    glm::vec3 position;

    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    line_t get_position();
    void tick();

    float t_x;
    float t_y;

    bounding_box_t bbox;

    float rotation;
    double dx;
    double dy;
    double gravity;
    double oscillator;
    long long int timer;
    bool danger;
    long long int life;
    double start_y;
    bool immunity;
    bool destroyed;

private:
    VAO *circle1;
    VAO *circle2;
    VAO *line1;
    VAO *line2;
};

#endif // BALL_H
