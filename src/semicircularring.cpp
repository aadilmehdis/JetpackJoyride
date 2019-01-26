#include "semicircularring.h"
#include "main.h"

SemiCircularRing::SemiCircularRing(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->dx = 0.01;
    this->dy = 0;
    this->gravity = 0.001;

    this->radius = 2;
    this->radius_inner = 1;
    this->center_x = x + this->radius;
    this->center_y = y - this->radius;

    this->entered = false;

    this->bbox.x = x; 
    this->bbox.y = y;
    this->bbox.height = radius;
    this->bbox.width = radius*2;

    int N=100;
	double pi = 3.1415926535897932384626433;
	GLfloat g_vertex_buffer_data1[9*N];
	GLfloat g_vertex_buffer_data2[9*N];
	double theta = 2 * pi / N;
	double SinTheta, CosTheta;
	SinTheta = sin(theta);
	CosTheta = cos(theta);

	float xx, yy, xx2, yy2;
	// xx = 0.0f;
	// yy = radius;
    // xx2 = 0.0f;
	// yy2 = radius_inner;
    xx = -1*radius;
	yy = 0.0f;
    xx2 = -1*radius_inner;
	yy2 = 0.0f;

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

    for(int i=0;i<9*N;i+=9)
	{
		g_vertex_buffer_data2[i+0] = 0.0f;
		g_vertex_buffer_data2[i+1] = 0.0f;
		g_vertex_buffer_data2[i+2] = 0.0f;

		g_vertex_buffer_data2[i+3] = xx2;
		g_vertex_buffer_data2[i+4] = yy2;
		g_vertex_buffer_data2[i+5] = 0.0f;

		g_vertex_buffer_data2[i+6] = xx2 * CosTheta + yy2 * SinTheta;
		g_vertex_buffer_data2[i+7] = yy2 * CosTheta - xx2 * SinTheta;
		g_vertex_buffer_data2[i+8] = 0.0f;

		xx2 = g_vertex_buffer_data2[i+6];
		yy2 = g_vertex_buffer_data2[i+7];
    }
    for(int i=0; i<9*N;++i)
    {
        if(i%3 == 0)
        {
            g_vertex_buffer_data1[i] += this->radius;
            g_vertex_buffer_data2[i] += this->radius;
        }
        else if(i%3 == 1)
        {
            g_vertex_buffer_data1[i] -= this->radius;
            g_vertex_buffer_data2[i] -= this->radius;
        }
    }
    this->ball = create3DObject(GL_TRIANGLES, 3*N/2, g_vertex_buffer_data1, COLOR_CYAN, GL_FILL);
    this->innerball = create3DObject(GL_TRIANGLES, 3*N/2, g_vertex_buffer_data2, COLOR_BACKGROUND, GL_FILL);
}

void SemiCircularRing::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->ball);
    draw3DObject(this->innerball);
}

void SemiCircularRing::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void SemiCircularRing::tick() {
    this->position.x -= this->dx;
    this->center_x = this->position.x+this->radius;
    this->bbox.x = this->position.x;
    this->bbox.y = this->position.y;
}

