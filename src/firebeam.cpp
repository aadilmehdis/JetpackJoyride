#include "firebeam.h"
#include "main.h"


FireBeam::FireBeam(float x, float y, color_t color )
{
    this->position = glm::vec3(x, y, 0);
    this->start_y = y;
    this->rotation = 0;
    this->dx = 0;
    this->dy = 0;
    this->gravity = 0.02;
    this->oscillator = 0;
    this->timer = 0;
    this->danger = false;
    this->life = 0;
    


    int N=6;
	double pi = 3.1415926535897932384626433;
	GLfloat g_vertex_buffer_data1[9*N];
	GLfloat g_vertex_buffer_data2[9*N];
	double theta = 2 * pi / N;
	double SinTheta, CosTheta;
	SinTheta = sin(theta);
	CosTheta = cos(theta);

    float length = 7.5, width = 0.1;
    this->bbox.x = x;
    this->bbox.y = y;
    this->bbox.height = 0.2;
    this->bbox.width = 7.5;

	float xx, yy, xx2, yy2;
	xx = 0.0f;
	yy = 0.5f;
    xx2 = 0.0f;
	yy2 = 0.5f;

    GLfloat g_vertex_buffer_data3[] = {
        0.0f, 0.0f, 0.0f,
        length, 0.0f, 0.0f,
        0.0f, width, 0.0f,

        length, 0.0f, 0.0f,
        0.0f, width, 0.0f,
        length, width, 0.0f,

        0.0f, 0.0f, 0.0f,
        length, 0.0f, 0.0f,
        0.0f, -width, 0.0f,

        length, 0.0f, 0.0f,
        0.0f, -width, 0.0f,
        length, -width, 0.0f,
    };

    GLfloat g_vertex_buffer_data4[] = {
        0.0f, 0.0f, 0.0f,
        length, 0.0f, 0.0f,
        0.0f, width-0.05, 0.0f,

        length, 0.0f, 0.0f,
        0.0f, width-0.05, 0.0f,
        length, width-0.05, 0.0f,

        0.0f, 0.0f, 0.0f,
        length, 0.0f, 0.0f,
        0.0f, -width+0.05, 0.0f,

        length, 0.0f, 0.0f,
        0.0f, -width+0.05, 0.0f,
        length, -width+0.05, 0.0f,
    };

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

        g_vertex_buffer_data2[i+0] = 0.0f;
		g_vertex_buffer_data2[i+1] = 0.0f;
		g_vertex_buffer_data2[i+2] = 0.0f;

		g_vertex_buffer_data2[i+3] = xx2;
		g_vertex_buffer_data2[i+4] = yy2;
		g_vertex_buffer_data2[i+5] = 0.0f;

		g_vertex_buffer_data2[i+6] = (xx2 * CosTheta + yy2 * SinTheta);
		g_vertex_buffer_data2[i+7] = (yy2 * CosTheta - xx2 * SinTheta);
		g_vertex_buffer_data2[i+8] = 0.0f;

		xx2 = g_vertex_buffer_data2[i+6];
		yy2 = g_vertex_buffer_data2[i+7];
	}
    
    for(int i=0;i<9*N;++i)
    {g_vertex_buffer_data1[i]=g_vertex_buffer_data1[i]/4;
    }
    for(int i=0;i<9*N;++i)
    {
        g_vertex_buffer_data2[i]=g_vertex_buffer_data2[i]/4;
        if((i+1)%3 != 0)
        {
            if((i+1)%3 == 1)
            {
                g_vertex_buffer_data2[i] += length;  
            }
        }
    }
    this->circle1 = create3DObject(GL_TRIANGLES, 3*N, g_vertex_buffer_data1, COLOR_ORANGE, GL_FILL);
    this->circle2 = create3DObject(GL_TRIANGLES, 3*N, g_vertex_buffer_data2, COLOR_ORANGE, GL_FILL);
    glLineWidth(2.0);
    this->line1 = create3DObject(GL_TRIANGLES, 12, g_vertex_buffer_data3, COLOR_EMERALD, GL_FILL);
    this->line2 = create3DObject(GL_TRIANGLES, 12, g_vertex_buffer_data4, COLOR_YELLOW, GL_FILL);


}

void FireBeam::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->timer % 400 > 180)
    {
        draw3DObject(this->line1);
        draw3DObject(this->line2);
        this->danger = true;
    }
    else 
    {
        this->danger = false;
    }

    draw3DObject(this->circle1);
    draw3DObject(this->circle2);


}

void FireBeam::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void FireBeam::tick() {
    this->timer += 1;
    this->oscillator += this->gravity;
    this->position.y = 1.8*sin(this->oscillator) + this->start_y;
    this->bbox.x = this->position.x;
    this->bbox.y = this->position.y;
    this->life += 1;
}
