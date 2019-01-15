#include "main.h"

#ifndef TILE_H
#define TILE_H


class Tile {
public:
    Tile() {}
    Tile(float x, float y, color_t color );
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
