#include "dragon.h"
#include "main.h"


Dragon::Dragon(float x, float y, color_t color )
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->dx = 0;
    this->dy = 0;
    this->gravity = 0.02;
    this->oscillator = 0;
    this->life = 0;

    GLfloat vertex_buffer_data1[] = {
        //face
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.5f, -1.0f, 0.0f,
        // face end
    };

    GLfloat vertex_buffer_data2[] = {
        //ears
        0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.25f, 0.5f, 0.0f,

        0.5f, 0.0f, 0.0f,
        0.75f, 0.5f, 0.0f,
        1.0f, 0.0f, 0.0f,
        //ears end

        //gills
        0.0f, 0.0f, 0.0f,
        0.0f, -0.5f, 0.0f,
        0.25f, -0.5f, 0.0f,

        1.0f, 0.0f, 0.0f,
        0.75f, -0.5f, 0.0f,
        1.0f, -0.5f, 0.0f,
        //gills end
    };

    GLfloat vertex_buffer_data3[] = {
        //nostrils
        0.5f, -0.5f, 0.0f,
        0.4f, -0.5f, 0.0f,
        0.45f, -0.3f, 0.0f,

        0.5f, -0.5f, 0.0f,
        0.6f, -0.5f, 0.0f,
        0.55f, -0.3f, 0.0f,
        //nostrils end

        //eyes
        0.2f, -0.2f, 0.0f,
        0.3f, -0.2f, 0.0f,
        0.25f, -0.1f, 0.0f,


        0.7f, -0.2f, 0.0f,
        0.8f, -0.2f, 0.0f,
        0.75f, -0.1f, 0.0f,


        //eyes end
    };

    this->object = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data1, COLOR_RED, GL_FILL);
    this->ears = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data2, COLOR_PURPLE, GL_FILL);
    this->eyes = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data3, COLOR_YELLOW, GL_FILL);
}

void Dragon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->ears);
    draw3DObject(this->eyes);
    // draw3DObject(this->lin);
}

void Dragon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Dragon::tick() {
    this->oscillator += this->gravity;
    this->position.y = 2*sin(this->oscillator) + 1;
    this->life +=1;
}

