#include "magnet.h"
#include "main.h"


Magnet::Magnet(float x, float y, color_t color )
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->dx = 0.01;
    this->dy = 0;
    this->gravity = 0.001;
    this->influence = 0.002;

    GLfloat vertex_buffer_north[] = {
        0.0f, 0.0f, 0.0f,
        0.1f, 0.0f, 0.0f,
        0.05f, 0.3f, 0.0f, 
    };
    GLfloat vertex_buffer_south[] = {
        0.0f, 0.0f, 0.0f,
        0.1f, 0.0f, 0.0f,
        0.05f, -0.3f, 0.0f, 
    };
    this->north = create3DObject(GL_TRIANGLES, 3, vertex_buffer_north, COLOR_CRIMSON, GL_FILL);
    this->south = create3DObject(GL_TRIANGLES, 3, vertex_buffer_south, COLOR_NAVY_BLUE, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->north);
    draw3DObject(this->south);
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Magnet::tick() {
    this->position.x -= this->dx;
}

