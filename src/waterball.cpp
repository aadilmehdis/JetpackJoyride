#include "waterball.h"
#include "main.h"

WaterBall::WaterBall(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->dx = 0.01;
    this->dy = 0;
    this->gravity = 0;

    this->radius = 0.2;

    this->bbox.x = x; 
    this->bbox.y = y;
    this->bbox.height = radius*2;
    this->bbox.width = radius*2;

    int N=100;
	double pi = 3.1415926535897932384626433;
	GLfloat g_vertex_buffer_data1[9*N];
	double theta = 2 * pi / N;
	double SinTheta, CosTheta;
	SinTheta = sin(theta);
	CosTheta = cos(theta);

	float xx, yy, xx2, yy2;
	xx = 0.0f;
	yy = radius;

	for(int i=0;i<9*N;i+=9)
	{
		g_vertex_buffer_data1[i+0] = 0.0f;
		g_vertex_buffer_data1[i+1] = 0.0f;
		g_vertex_buffer_data1[i+2] = 0.0f;

		g_vertex_buffer_data1[i+3] = xx;
		g_vertex_buffer_data1[i+4] = yy;
		g_vertex_buffer_data1[i+5] = 0.0f;

		g_vertex_buffer_data1[i+6] = xx * CosTheta + yy * SinTheta;
		g_vertex_buffer_data1[i+7] = yy * CosTheta - xx * SinTheta;
		g_vertex_buffer_data1[i+8] = 0.0f;

		xx = g_vertex_buffer_data1[i+6];
		yy = g_vertex_buffer_data1[i+7];
    }
    GLfloat g_vertex_buffer_data2[] = {
        
    };
    for(int i=0; i<9*N;++i)
    {
        if(i%3 == 0)
        {
            g_vertex_buffer_data1[i] += this->radius;
        }
        else if(i%3 == 1)
        {
            g_vertex_buffer_data1[i] -= this->radius;
        }
    }
    this->ball = create3DObject(GL_TRIANGLES, 3*N, g_vertex_buffer_data1, color, GL_FILL);
    // this->bound = create3DObject(GL_LINE_LOOP, 4, g_vertex_buffer_data2, color, GL_FILL);
}

void WaterBall::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    // draw3DObject(this->bound);
}

void WaterBall::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void WaterBall::tick() {
    this->position.x -= dx;
    this->bbox.x = this->position.x;
    this->bbox.y = this->position.y;
}

