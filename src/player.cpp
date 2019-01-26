#include "player.h"
#include "main.h"


Player::Player(float x, float y, color_t color )
{
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->dx = 0.02;
    this->dy = 0;
    this->gravity = 0.001;
    this->score = 0;
    this->ring_immune = false;

    this->magenetic_power = false;
    this->immunity = false;

    this->ring_influence = false;
    this->init_pos_x = 0;
    this->init_pos_y = 0;
    this->check = false;


    this->magenetic_power_timer = 0;
    this->immunity_timer = 0;
    this->life = 5;


    this->bbox.x = x;
    this->bbox.y = y;
    this->bbox.height = 1.15;
    this->bbox.width = 0.60;

    this->prev_pos_x = x;
    // this->bbox.x = x;
    // this->bbox.y = y;
    // this->bbox.height = 1;
    // this->bbox.width = 1;


    int N=100;
	double pi = 3.1415926535897932384626433;
	GLfloat g_vertex_buffer_head[9*N];
	double theta = 2 * pi / N;
	double SinTheta, CosTheta;
	SinTheta = sin(theta);
	CosTheta = cos(theta);

	float xx, yy;
	xx = 0.0f;
	yy = 0.15f;

	for(int i=0;i<9*N;i+=9)
	{
		g_vertex_buffer_head[i+0] = 0.0f;
		g_vertex_buffer_head[i+1] = 0.0f;
		g_vertex_buffer_head[i+2] = 0.0f;

		g_vertex_buffer_head[i+3] = xx;
		g_vertex_buffer_head[i+4] = yy;
		g_vertex_buffer_head[i+5] = 0.0f;

		g_vertex_buffer_head[i+6] = xx * CosTheta + yy * SinTheta;
		g_vertex_buffer_head[i+7] = yy * CosTheta - xx * SinTheta;
		g_vertex_buffer_head[i+8] = 0.0f;

		xx = g_vertex_buffer_head[i+6];
		yy = g_vertex_buffer_head[i+7];
	}
    
    GLfloat g_vertex_buffer_torso[] = {
        -0.18f, -0.15f, 0.0f,
        0.18f, -.15f, 0.0f,
        -0.18f, -.7f, 0.0f,

        0.18f, -.15f, 0.0f,
        -0.18f, -.7f, 0.0f,
        0.18f, -.7f, 0.0f,

    };

    GLfloat g_vertex_buffer_jetpack[] = {

        -0.18f, -0.2f, 0.0f,
        -0.18f, -0.5f, 0.0f,
        -0.3f, -0.5f, 0.0f,

        -0.18f, -0.2f, 0.0f,
        -0.25f, -0.2f, 0.0f,
        -0.3f, -0.5f, 0.0f,

    };

    GLfloat g_vertex_buffer_leg[] = {

        -0.05f,-0.7f,0.0f,
        0.05f,-0.7f,0.0f,
        -0.05f,-1.0f, 0.0f,

        0.05f,-0.7f,0.0f,
        -0.05f,-1.0f, 0.0f,
        0.05f,-1.0f,0.0f,

        0.18f, -0.2f, 0.0f,
        0.18f, -0.3f, 0.0f,
        0.3f, -0.3f, 0.0f,

        0.18f, -0.2f, 0.0f,
        0.25f, -0.2f, 0.0f,
        0.3f, -0.3f, 0.0f,

        0.05f, -0.9f, 0.0f,
        0.05f, -1.0f, 0.0f,
        0.18f, -1.0f, 0.0f,
    };

    GLfloat g_vertex_bbox[] = {
        // this->bbox.x, this->bbox.y, 0.0f,
        // this->bbox.x, this->bbox.y + this->bbox.height, 0.0f,
        // this->bbox.x + this->bbox.width, this->bbox.y + this->bbox.height, 0.0f,
        // this->bbox.x + this->bbox.width, this->bbox.y, 0.0f,

        0.0f,0.0f,0.0f,
        0.0f,-1.15f,0.0f,
        0.6f,-1.15f,0.0f,
        0.6f,0.0f,0.0f,

    };
    
    for(int i=0;i<9*N;++i)
    {
        if(i%3 == 0)
        {
            g_vertex_buffer_head[i] += 0.3;
        }
        else if(i%3 == 1)
        {
            g_vertex_buffer_head[i] -= 0.15;
        }
        else
        {
            ;
        }
    }
    for(int i=0;i<3*6;++i)
    {
        if(i%3 == 0)
        {
            g_vertex_buffer_jetpack[i] += 0.3;
            g_vertex_buffer_torso[i] +=0.3;
        }
        else if(i%3 == 1)
        {
            g_vertex_buffer_jetpack[i] -= 0.3;
            g_vertex_buffer_torso[i] -= 0.15;
        }
        else
        {
            ;
        }
    }
    for(int i=0;i<15*3;++i)
    {
        if(i%3 == 0)
        {
            g_vertex_buffer_leg[i] += 0.3;
        }
        else if(i%3 == 1)
        {
            g_vertex_buffer_leg[i] -= 0.15;
        }
        else
        {
            ;
        }
    }


    // GLfloat g_vertex_buffer_jetpack[] = {

    //     0.0f, 0.0f, 0.0f,
    //     1.0f, 0.0f, 0.0f,
    //     0.0f, -1.0f, 0.0f,

    //     1.0f, 0.0f, 0.0f,
    //     0.0f, -1.0f, 0.0f,
    //     1.0f, -1.0f, 0.0f,
    
    // };
    
    this->head = create3DObject(GL_TRIANGLES, 3*N, g_vertex_buffer_head, COLOR_GREEN, GL_FILL);
    this->torso = create3DObject(GL_TRIANGLES, 6, g_vertex_buffer_torso, COLOR_PURPLE, GL_FILL);
    this->leg = create3DObject(GL_TRIANGLES, 15, g_vertex_buffer_leg, COLOR_NAVY_BLUE, GL_FILL);
    this->jetpack = create3DObject(GL_TRIANGLES, 6, g_vertex_buffer_jetpack, COLOR_RED, GL_FILL);
    // this->object = create3DObject(GL_LINE_LOOP, 4, g_vertex_bbox, COLOR_BLACK, GL_FILL);

}

void Player::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    draw3DObject(this->head);
    draw3DObject(this->torso);
    draw3DObject(this->leg);
    draw3DObject(this->jetpack);
    // draw3DObject(this->object);
}

void Player::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Player::tick() {
    if(!this->ring_influence)
    {
        if(this->magenetic_power)
        {
            this->magenetic_power_timer +=1;
            if(this->magenetic_power_timer == 300)
            {
                this->magenetic_power_timer = 0;
                this->magenetic_power = false;
            }
        }
        if(this->immunity)
        {
            this->immunity_timer += 1;
            if(this->immunity_timer == 300)
            {
                this->immunity_timer = 0;
                this->immunity = false;
            }
        }


        this->position.y -= dy;
        if(this->position.y < -1.35)
        {
            this->dy = 0;
            this->position.y = -1.35;
        }
        else
        {
            this->dy += this->gravity;
        }

        if(this->position.y > 4)
        {
            this->position.y = 4;
            this->dy = 0;
        }
        if(this->position.x < -4.0)
        {
        this->position.x = -4.0;
        }
        this->bbox.x = this->position.x;
        this->bbox.y = this->position.y;
        this->prev_pos_x = this->position.x;
    }
    else
    {
        this->prev_pos_x += 0.02;
        this->position.x += 0.02;
        this->position.y = sqrt((1 - pow(this->position.x - this->init_pos_x + 1,2) )) + init_pos_y;
        
        if(isnan(this->position.y))
        {
            this->position.y = -1.35;
            this->ring_influence = false;
            this->ring_immune = false;
        }

    }
}

