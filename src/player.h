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
    long long int score;

    bool magenetic_power;
    bool immunity;
    bool ring_influence;
    int life;
    int magenetic_power_timer;
    int immunity_timer;
    float init_pos_x;
    float init_pos_y;
    bool check;
    bool ring_immune;
    float prev_pos_x;

    
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
