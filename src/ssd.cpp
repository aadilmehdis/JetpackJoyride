#include "ssd.h"
#include "main.h"


SSD::SSD(float x, float y, color_t color )
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->dx = 0;
    this->dy = 0;
    this->gravity = 0.001;
    this->digit = 0;

    GLfloat vertex_buffer_a[] = {
        0.0f, 0.0f, 0.0f,
        0.0f,-0.1f,0.0f,
        0.3f,0.0f,0.0f,

        0.0f,-0.1f,0.0f,
        0.3f,0.0f,0.0f,
        0.3f,-0.1f,0.0f,
    };
    GLfloat vertex_buffer_b[] = {
        0.2f,-0.0f,0.0f,
        0.3f,-0.0f,0.0f,
        0.2f,-0.3f, 0.0f,
        0.3f,-0.0f,0.0f,
        0.2f,-0.3f, 0.0f,
        0.3f,-0.3f, 0.0f,
    };
    GLfloat vertex_buffer_c[] = {
        0.2f,-0.3f,0.0f,
        0.3f,-0.3f,0.0f,
        0.2f,-0.7f, 0.0f,
        0.3f,-0.3f,0.0f,
        0.2f,-0.7f, 0.0f,
        0.3f,-0.7f, 0.0f,

    };
    GLfloat vertex_buffer_g[] = {
        0.0f, -0.3f, 0.0f,
        0.0f,-0.4f,0.0f,
        0.3f,-0.3f,0.0f,

        0.0f,-0.4f,0.0f,
        0.3f,-0.3f,0.0f,
        0.3f,-0.4f,0.0f,
    };
    GLfloat vertex_buffer_e[] = {
        0.0f,-0.3f,0.0f,
        0.1f,-0.3f,0.0f,
        0.0f,-0.7f, 0.0f,
        0.1f,-0.3f,0.0f,
        0.0f,-0.7f, 0.0f,
        0.1f,-0.7f, 0.0f,
    };
    GLfloat vertex_buffer_f[] = {
        0.0f,-0.0f,0.0f,
        0.1f,-0.0f,0.0f,
        0.0f,-0.3f, 0.0f,
        0.1f,-0.0f,0.0f,
        0.0f,-0.3f, 0.0f,
        0.1f,-0.3f, 0.0f,
    };
    GLfloat vertex_buffer_d[] = {
        0.0f, -0.6f, 0.0f,
        0.0f,-0.7f,0.0f,
        0.3f,-0.6f,0.0f,

        0.0f,-0.7f,0.0f,
        0.3f,-0.6f,0.0f,
        0.3f,-0.7f,0.0f,
    };
    for(int i=0;i<6*3;++i)
    {
        vertex_buffer_a[i] /= 2;
        vertex_buffer_b[i] /= 2;
        vertex_buffer_c[i] /= 2;
        vertex_buffer_d[i] /= 2;
        vertex_buffer_e[i] /= 2;
        vertex_buffer_f[i] /= 2;
        vertex_buffer_g[i] /= 2;
    }

    this->a = create3DObject(GL_TRIANGLES, 6, vertex_buffer_a, COLOR_WHITE, GL_FILL);
    this->b = create3DObject(GL_TRIANGLES, 6, vertex_buffer_b, COLOR_WHITE, GL_FILL);
    this->c = create3DObject(GL_TRIANGLES, 6, vertex_buffer_c, COLOR_WHITE, GL_FILL);
    this->d = create3DObject(GL_TRIANGLES, 6, vertex_buffer_d, COLOR_WHITE, GL_FILL);
    this->e = create3DObject(GL_TRIANGLES, 6, vertex_buffer_e, COLOR_WHITE, GL_FILL);
    this->f = create3DObject(GL_TRIANGLES, 6, vertex_buffer_f, COLOR_WHITE, GL_FILL);
    this->g = create3DObject(GL_TRIANGLES, 6, vertex_buffer_g, COLOR_WHITE, GL_FILL);
}

void SSD::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->digit == 0)
    {
        draw3DObject(this->a);draw3DObject(this->b);
        draw3DObject(this->c);draw3DObject(this->d);
        draw3DObject(this->e);draw3DObject(this->f);
    }
    else if(this->digit == 1)
    {
        draw3DObject(this->b);draw3DObject(this->c);
    }
    else if(this->digit == 2)
    {
        draw3DObject(this->a);draw3DObject(this->b);
        draw3DObject(this->d);draw3DObject(this->e);
        draw3DObject(this->g);
    }
    else if(this->digit == 3)
    {
        draw3DObject(this->a);draw3DObject(this->b);
        draw3DObject(this->c);draw3DObject(this->d);
        draw3DObject(this->g);
    }
    else if(this->digit == 4)
    {
        draw3DObject(this->b);draw3DObject(this->c);
        draw3DObject(this->f);draw3DObject(this->g);
    }
    else if(this->digit == 5)
    {
        draw3DObject(this->a);draw3DObject(this->c);
        draw3DObject(this->d);draw3DObject(this->f);
        draw3DObject(this->g);
    }
    else if(this->digit == 6)
    {
        draw3DObject(this->a);draw3DObject(this->c);
        draw3DObject(this->d);draw3DObject(this->e);
        draw3DObject(this->f);draw3DObject(this->g);
    }
    else if(this->digit == 7)
    {
        draw3DObject(this->a);draw3DObject(this->b);
        draw3DObject(this->c);
    }
    else if(this->digit == 8)
    {
        draw3DObject(this->a);draw3DObject(this->b);
        draw3DObject(this->c);draw3DObject(this->d);
        draw3DObject(this->e);draw3DObject(this->f);
        draw3DObject(this->g);
    }
    else if(this->digit == 9)
    {
        draw3DObject(this->a);draw3DObject(this->b);
        draw3DObject(this->c);draw3DObject(this->d);
        draw3DObject(this->f);draw3DObject(this->g);
    }

}

void SSD::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void SSD::tick() {
    ;
}

void SSD::set_digit(int dig) {
    this->digit = dig;
}