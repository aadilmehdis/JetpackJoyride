#include "boomerang.h"
#include "main.h"


Boomerang::Boomerang(float x, float y, color_t color )
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->dx = -0.055;
    this->dy = 0.006;
    this->gravity = 0.0001;

    GLfloat vertex_buffer_data1[] = {

        0.0f, 0.0f, 0.0f,
        0.0f, -0.5f, 0.0f,
        0.25f, -0.5f, 0.0f,


        // 0.0f, 0.0f, 0.0f,
        // 0.5f, 0.0f, 0.0f,
        // 0.25f, 0.2f, 0.0f,
    };
    GLfloat vertex_buffer_data2[] = {
        0.0f, -0.25f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,

        // 0.0f, 0.0f, 0.0f,
        // 0.5f, 0.0f, 0.0f,
        // 0.25f, -0.2f, 0.0f,
    };
    this->upperhead = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data1, COLOR_GOLD, GL_FILL);
    this->lowerhead = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data2, COLOR_ORANGE, GL_FILL);
    
}

void Boomerang::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->upperhead);
    draw3DObject(this->lowerhead);
}

void Boomerang::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Boomerang::tick() {

    this->position.x += this->dx;
    this->position.y -= this->dy;
    this->dx += this->gravity;
    this->rotation += 1;
}

