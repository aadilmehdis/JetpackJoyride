#include "fireline.h"
#include "main.h"


FireLine::FireLine(float x, float y, color_t color )
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->dx = 0.01;
    this->dy = 0;
    this->gravity = 0;
    this->danger = true;

    
    float end_x = rand()%(10) + (-5);
    float end_y = rand()%(10) + (0);

    this->t_x = end_x/4;
    this->t_y = end_y/4;

    this->line_coords.x1 = 0;
    this->line_coords.y1 = 0;
    this->line_coords.x2 = end_x/4;
    this->line_coords.y2 = end_y/4;

    while(abs(end_x) == abs(end_y) && abs(end_x) > 5) {
        end_x = rand()%(20) + (-10);
    }



    int N=6;
	double pi = 3.1415926535897932384626433;
	GLfloat g_vertex_buffer_data1[9*N];
	GLfloat g_vertex_buffer_data2[9*N];
	double theta = 2 * pi / N;
	double SinTheta, CosTheta;
	SinTheta = sin(theta);
	CosTheta = cos(theta);

	float xx, yy, xx2, yy2;
	xx = 0.0f;
	yy = 0.5f;
    xx2 = 0.0f;
	yy2 = 0.5f;

    GLfloat g_vertex_buffer_data3[] = {
        0.0f, 0.0f, 0.0f,
        end_x/4, end_y/4, 0.0f,
        0.03f, 0.03f, 0.0f,
        end_x/4, end_y/4, 0.0f,
        0.03f, 0.03f, 0.0f,
        end_x/4+0.03, end_y/4+0.03, 0.0f,

        0.0f, 0.0f, 0.0f,
        end_x/4, end_y/4, 0.0f,
        -0.03f, -0.03f, 0.0f,
        end_x/4, end_y/4, 0.0f,
        -0.03f, -0.03f, 0.0f,
        end_x/4-0.03, end_y/4-0.03, 0.0f,
    };

    GLfloat g_vertex_buffer_data4[] = {
        0.0f, 0.0f, 0.0f,
        end_x/4, end_y/4, 0.0f,
        0.05f, 0.05f, 0.0f,
        end_x/4, end_y/4, 0.0f,
        0.05f, 0.05f, 0.0f,
        end_x/4+0.05, end_y/4+0.05, 0.0f,

        0.0f, 0.0f, 0.0f,
        end_x/4, end_y/4, 0.0f,
        -0.05f, -0.05f, 0.0f,
        end_x/4, end_y/4, 0.0f,
        -0.05f, -0.05f, 0.0f,
        end_x/4-0.05, end_y/4-0.05, 0.0f,
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
        if((i+1)%3 != 0)
        {
            if((i+1)%3 == 1)
            {
                g_vertex_buffer_data2[i] += end_x;  
            }
            else 
            {
                g_vertex_buffer_data2[i] += end_y; 
            }
        }
        g_vertex_buffer_data2[i]=g_vertex_buffer_data2[i]/4;
    }
    this->circle1 = create3DObject(GL_TRIANGLES, 3*N, g_vertex_buffer_data1, COLOR_SILVER, GL_FILL);
    this->circle2 = create3DObject(GL_TRIANGLES, 3*N, g_vertex_buffer_data2, COLOR_SILVER, GL_FILL);
    glLineWidth(2.0);
    this->line1 = create3DObject(GL_TRIANGLES, 12, g_vertex_buffer_data3, COLOR_FLAME, GL_FILL);
    this->line2 = create3DObject(GL_TRIANGLES, 12, g_vertex_buffer_data4, COLOR_GOLD, GL_FILL);
    // this->line1 = create3DObject(GL_LINES, 2, g_vertex_buffer_data3, COLOR_FLAME, GL_FILL);

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
    if(this->danger)
    {
        draw3DObject(this->line2);
        draw3DObject(this->line1);
    }
    draw3DObject(this->circle1);
    draw3DObject(this->circle2);

}

void FireLine::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void FireLine::tick() {
    this->position.x -= this->dx;
    this->line_coords.x1 = this->position.x;
    this->line_coords.y1 = this->position.y;
    this->line_coords.x2 = this->position.x + this->t_x;
    this->line_coords.y2 = this->position.y + this->t_y;
    // this->position.y -= speed;
}

line_t FireLine::get_position(){
    return this->line_coords;
}
