#include "window.h"
#include "main.h"


Window::Window(float x, float y, color_t color )
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->dx = 0.01;
    this->dy = 0;
    this->gravity = 0.001;

    GLfloat vertex_buffer_data[] = {
        0.0f, 0.0f, 0.0f,
        2.0f, 0.0f, 0.f,
        0.0f, 8.0f, 0.f,

        2.0f, 8.0f, 0.0f,
        2.0f, 0.0f, 0.f,
        0.0f, 8.0f, 0.f,

    };
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_WINDOW, GL_FILL);
}

void Window::draw(glm::mat4 VP) {
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

void Window::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Window::tick() {
    this->position.x -= this->dx;
}

