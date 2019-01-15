#include "fireline.h"
#include "main.h"


FireLine::FireLine(float x, float y, color_t color )
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->dx = 0.01;
    this->dy = 0;
    this->gravity = 0;

    
    float end_x = rand()%(20) + (-10);
    float end_y = rand()%(10) + (0);
    while(abs(end_x) == abs(end_y) && abs(end_x) > 5) {
        end_x = rand()%(20) + (-10);
    }

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
    };
    for(int i=0;i<24*3;++i)
    {vertex_buffer_data[i]=vertex_buffer_data[i]/8;
    }
    this->object = create3DObject(GL_TRIANGLES, 24, vertex_buffer_data, color, GL_FILL);
}

void FireLine::draw(glm::mat4 VP) {
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

void FireLine::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void FireLine::tick() {
    ;
    this->position.x -= this->dx;
    // this->position.y -= speed;
}

