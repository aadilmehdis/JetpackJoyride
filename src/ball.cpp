#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    float end_x = 10.0f;
    float end_y = 0.0f;
    GLfloat vertex_buffer_data[] = {

        0.0f, 0.0f, 0.0f,  
        2.0f, 0.0f, 0.0f,
        0.0f, 2.0f, 0.0f,
        0.0f, 2.0f, 0.0f,
        2.0f, 0.0f, 0.0f,
        2.0f, 2.0f, 0.0f,

        1.0f, 1.0f, 0.0f,
        1.5f, 0.5f, 0.0f,
        end_x+1, end_y+1, 0.0f,

        end_x+1.5, end_y+0.5, 0.0f,
        1.5f, 0.5f, 0.0f,
        end_x+1, end_y+1, 0.0f,

        1.0f, 1.0f, 0.0f,
        0.5f, 1.5f, 0.0f,
        end_x+1, end_y+1, 0.0f,

        end_x+0.5, end_y+1.5, 0.0f,
        0.5f, 1.5f, 0.0f,
        end_x+1, end_y+1, 0.0f,


        end_x, end_y, 0.0f,
        (end_x+2), end_y, 0.0f,
        end_x, (end_y+2), 0.0f,
        (end_x+2), (end_y+2), 0.0f,
        (end_x+2), end_y, 0.0f,
        end_x, (end_y+2), 0.0f,

        0.0f, 0.0f, 0.0f,
        2.0f, 0.0f, 0.0f,
        2.0f, 5.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 5.0f, 0.0f,
        2.0f, 5.0f, 0.0f,

    };

    for(int i=0;i<24*3;++i)
    {vertex_buffer_data[i]=vertex_buffer_data[i]/4;
        printf("%ff, ",vertex_buffer_data[i]/4);
    }
    this->object = create3DObject(GL_TRIANGLES, 30, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

