#include "iceball.h"
#include "main.h"

IceBall::IceBall(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->dx = 0.05;
    this->dy = 0;
    this->gravity = 0.001;

    this->bbox.x = x - 0.25; 
    this->bbox.y = y + 0.25;
    this->bbox.height = 0.5;
    this->bbox.width = 0.5;

    GLfloat g_vertex_buffer_data[] = {
        0.05f, -0.1f, 0.0f,
        0.45f, -0.1f, 0.0f,
        0.25f, -0.5f, 0.0f,

        0.05f, -0.4f, 0.0f,
        0.45f, -0.4f, 0.0f,
        0.25f, -0.0f, 0.0f,
    };

    for(int i=0;i<6*3;++i)
    {
        if(i%3==0)
        {
            g_vertex_buffer_data[i] -= 0.25;
        }
        if(i%3==1)
        {
            g_vertex_buffer_data[i] += 0.25;
        }
    }
    this->ball = create3DObject(GL_TRIANGLES, 6, g_vertex_buffer_data, COLOR_CYAN, GL_FILL);
}

void IceBall::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->ball);
}

void IceBall::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void IceBall::tick() {
    this->rotation += 2;
    this->position.x -= dx;
    this->dy += this->gravity;
    this->position.y -= dy;
    this->bbox.x = this->position.x - 0.25;
    this->bbox.y = this->position.y + 0.25; 
}

