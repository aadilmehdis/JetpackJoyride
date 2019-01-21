#include "main.h"

#ifndef PLAYER_H
#define PLAYER_H


class Player {
public:
    Player() {}
    Player(float x, float y, color_t color );
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
    // VAO *object;

    VAO *head;
    VAO *torso;
    VAO *leg;
    VAO *jetpack;
    // VAO *box;
};

#endif // BALL_H
