#include "main.h"
#include "timer.h"
#include "ball.h"
#include "fireline.h"
#include "player.h"
#include "boomerang.h"
#include "ground.h"
#include "tile.h"
#include "window.h"
#include "dragon.h"
#include "fuelbullet.h"
#include "coin.h"
#include "firebeam.h"
#include "magnet.h"
#include "powerup.h"
#include "ssd.h"
#include "waterball.h"
#include "iceball.h"
#include "semicircularring.h"


#include <vector>

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Player player;
Ground ground;
SemiCircularRing ring;
int LEVEL = 1;
float LEVEL_2_SPEED = 0.02;
float LEVEL_3_SPEED = 0.04;




long long int Frame=0;

vector<FireLine> fire_lines;
vector<Boomerang> boomerangs;
vector<Window> windows;
vector<Tile> tiles;
vector<FuelBullet> fuel_bullets;
vector<WaterBall> water_balls;
vector<IceBall> ice_balls;
vector<Coin> coins;
vector<FireBeam> fire_beams;
vector<Magnet> magnets;
vector<Dragon> dragons;
vector<PowerUp> powerups;
vector<SSD> ssd;
vector<SemiCircularRing> rings;


float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;


float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

Timer wall_timer(10.0 / 1);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye (0,0,1);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    // ball1.draw(VP);
    // ball2.draw(VP);

    ground.draw(VP);
    for(int i=0; i<windows.size(); ++i)
    {
        windows[i].draw(VP);
    }
    for(int i=0; i<tiles.size(); ++i)
    {
        tiles[i].draw(VP);
    }
    for(int i=0; i<rings.size(); ++i)
    {
        rings[i].draw(VP);
    }
    for(int i=0;i<fire_lines.size();++i)
    {
        fire_lines[i].draw(VP);
    }
    for(int i=0;i<fire_beams.size();++i)
    {
        fire_beams[i].draw(VP);
    }
    for(int i=0;i<dragons.size();++i)
    {
        dragons[i].draw(VP);
    }
    for(int i=0;i<boomerangs.size();++i)
    {
        boomerangs[i].draw(VP);
    }
    for(int i=0;i<magnets.size();++i)
    {
        magnets[i].draw(VP);
    }
    for(int i=0; i<fuel_bullets.size(); ++i)
    {
        fuel_bullets[i].draw(VP);
    }
    for(int i=0; i<water_balls.size(); ++i)
    {
        water_balls[i].draw(VP);
    }
    for(int i=0; i<ice_balls.size(); ++i)
    {
        ice_balls[i].draw(VP);
    }
    for(int i=0; i<coins.size(); ++i)
    {
        coins[i].draw(VP);
    }
    for(int i=0;i<powerups.size();++i)
    {
        powerups[i].draw(VP);
    }

    player.draw(VP);

    for(int i=0;i<ssd.size();++i)
    {
        ssd[i].draw(VP);
    }

}

void tick_input(GLFWwindow *window) {
    int left        = glfwGetKey(window, GLFW_KEY_LEFT);
    int right       = glfwGetKey(window, GLFW_KEY_RIGHT);
    int space          = glfwGetKey(window, GLFW_KEY_SPACE);
    int up          = glfwGetKey(window, GLFW_KEY_UP);
    int down        = glfwGetKey(window, GLFW_KEY_DOWN);
    int shoot       = glfwGetKey(window, GLFW_KEY_S);

    if(shoot) {
        if(Frame%10 == 0)
        {
            water_balls.push_back(WaterBall(player.position.x+0.3, player.position.y));
        }
    }
    if (up || space) {
        player.dy -= 0.005;
        if(Frame%10 == 0)
        {
            fuel_bullets.push_back(FuelBullet(player.position.x, player.position.y-0.8, COLOR_GOLD));
        }
    }
    if(down) {
        player.dy += 0.002;
    }
    if(left) {
        player.position.x -= player.dx; 
    }
    if(right) {
        if(player.position.x <= (0-1.0))
        {
            player.position.x += player.dx;   
        }
        else
        {
            Frame += 1;
            for(int i=0;i<fire_lines.size();++i)
            {
                fire_lines[i].dx = (LEVEL+2)*player.dx;
            } 
            for(int i=0;i<windows.size();++i)
            {
                windows[i].dx = (LEVEL+2)*player.dx;
            }
            for(int i=0;i<tiles.size();++i)
            {
                tiles[i].dx = (LEVEL+2)*player.dx;
            } 
            for(int i=0;i<coins.size();++i)
            {
                coins[i].dx = (LEVEL+2)*player.dx;
            } 
            for(int i=0;i<magnets.size();++i)
            {
                magnets[i].dx = (LEVEL+2)*player.dx;
            } 
            for(int i=0;i<rings.size();++i)
            {
                rings[i].dx = (LEVEL+2)*player.dx;
            }
        }
    }
}

void update_object_vectors() {
    for(int i=0; i<powerups.size();++i)
    {
        if(powerups[i].position.x < -6 || detect_collision(player.bbox, powerups[i].bbox))
        {
            if(detect_collision(player.bbox, powerups[i].bbox))
            {
                if(powerups[i].type == 0)
                {
                    player.immunity = true;
                }
                else if(powerups[i].type == 1)
                {
                    player.life += 1;
                }
                else if(powerups[i].type == 2)
                {
                    player.magenetic_power = true;
                }
            }
            powerups.erase(powerups.begin() + i);
        }
    }
    for(int i=0; i<dragons.size();++i)
    {
        if(dragons[i].life == 600)
        {
            dragons.erase(dragons.begin() + i);
        }
    }
    for(int i=0;i<magnets.size();++i)
    {
        if(LEVEL == 2)
        {
            magnets[i].dx = LEVEL_2_SPEED;
        }
        else if(LEVEL == 3)
        {
            magnets[i].dx = LEVEL_3_SPEED;
        }
        if(magnets[i].position.x < -5)
        {
            magnets.erase(magnets.begin() + i);
        }
    }
    for(int i=0;i<fire_beams.size();++i)
    {
        if(fire_beams[i].life == 1500)
        {
            fire_beams.erase(fire_beams.begin() + i);
        }
    }
    for(int i=0;i<fire_lines.size();++i)
    {
        if(LEVEL == 2)
        {
            fire_lines[i].dx = LEVEL_2_SPEED;
        }
        else if(LEVEL == 3)
        {
            fire_lines[i].dx = LEVEL_3_SPEED;
        }
        if(fire_lines[i].position.x < -5)
        {
            fire_lines.erase(fire_lines.begin() + i);
        }
    } 
    
    for(int i=0;i<boomerangs.size();++i)
    {
        if(detect_collision(boomerangs[i].bbox, player.bbox) && !player.ring_immune)
        {
            --player.life;
            boomerangs.erase(boomerangs.begin() + i );
            continue;
        }
        if(boomerangs[i].dx > 2)
        {
            boomerangs.erase(boomerangs.begin() + i );
        }
    }  
    for(int i=0;i<windows.size();++i)
    {
        if(LEVEL == 2)
        {
            windows[i].dx = LEVEL_2_SPEED;
        }
        else if(LEVEL == 3)
        {
            windows[i].dx = LEVEL_3_SPEED;
        }
        if(windows[i].position.x < -10)
        {
            windows.erase(windows.begin() + i );
        }
    }
    for(int i=0;i<tiles.size();++i)
    {
        if(LEVEL == 2)
        {
            tiles[i].dx = LEVEL_2_SPEED;
        }
        else if(LEVEL == 3)
        {
            tiles[i].dx = LEVEL_3_SPEED;
        }
        if(tiles[i].position.x < -10)
        {
            tiles.erase(tiles.begin() + i );
        }
    }
    for(int i=0;i<fuel_bullets.size();++i)
    {
        if(fuel_bullets[i].position.y < -2.5)
        {
            fuel_bullets.erase(fuel_bullets.begin() + i );
        }
    }
    for(int i=0;i<water_balls.size();++i)
    {
        bool balloon_burst = false;
        for(int j=0;j<fire_lines.size();++j)
        {
            if(!fire_lines[i].destroyed && detect_line_rectangle_collision(water_balls[i].bbox, fire_lines[i].line_coords))
            {
                water_balls.erase(water_balls.begin() + i );
                fire_lines[i].destroyed = true;
                balloon_burst = true;
                break;
            }
        }
        if(balloon_burst) continue;
        for(int j=0;j<fire_beams.size();++j)
        {
            if(!fire_beams[i].destroyed && detect_collision(water_balls[i].bbox, fire_beams[i].bbox))
            {
                water_balls.erase(water_balls.begin() + i );
                fire_beams[i].destroyed = true;
                balloon_burst = true;
                break;
            }
        }
        if(balloon_burst) continue;
        if(water_balls[i].position.y < -2.5)
        {
            water_balls.erase(water_balls.begin() + i );
        }
    }
    for(int i=0;i<ice_balls.size();++i)
    {
        if(detect_collision(ice_balls[i].bbox, player.bbox) && !player.ring_immune)
        {
            --player.life;
            ice_balls.erase(ice_balls.begin() + i );
            continue;
        }
        if(ice_balls[i].position.y < -2.5)
        {
            ice_balls.erase(ice_balls.begin() + i );
        }
    }
    for(int i=0; i<rings.size();++i)
    {
        if(LEVEL == 2)
        {
            rings[i].dx = LEVEL_2_SPEED;
        }
        else if(LEVEL == 3)
        {
            rings[i].dx = LEVEL_3_SPEED;
        }
        if(detect_collision(player.bbox, rings[i].bbox) && !rings[i].entered)
        {
            rings[i].entered = true;
            player.ring_influence = true;
            player.ring_immune = true;
            player.position.x = rings[i].position.x;
            player.position.y = rings[i].position.y - rings[i].bbox.height;
            player.init_pos_x = rings[i].center_x;
            player.init_pos_y = rings[i].center_y;
        }
        if(rings[i].position.x < -10)
        {
            rings.erase(rings.begin() + i );
        }
    }
    for(int i=0;i<coins.size();++i)
    {
        if(LEVEL == 2)
        {
            coins[i].dx = LEVEL_2_SPEED;
        }
        else if(LEVEL == 3)
        {
            coins[i].dx = LEVEL_3_SPEED;
        }
        if(detect_collision(player.bbox, coins[i].bbox))
        {
            if(coins[i].special_coin)
            {
                player.score += 5;
            }
            else
            {
                player.score += 1;
            }
            coins.erase(coins.begin() + i );
        }
        if(coins[i].position.x < -5)
        {
            coins.erase(coins.begin() + i );
        }
        //check for collision here itself for collecting coins. and erasing them.
    }
}

void make_rectangle_coins() {
    float coin_space = 0.42;
    int y_pos = rand()%4 + (0);
    for(int i=0; i<4; ++i)
    {
        for(int j=0 ; j<3; ++j)
        {
            int toss = rand()%15 + (0);
            if(toss == 0)
            {
                coins.push_back(Coin(15 + i * coin_space, y_pos + j * coin_space, COLOR_CRIMSON, true));
            }
            else 
            {
                coins.push_back(Coin(15 + i * coin_space, y_pos + j * coin_space, COLOR_GOLD, false));
            }
        }
    }
}

void make_ring_coins() {
    float coin_space = 0.36;
    int y_pos = rand()%4 + (0);
    for(int i=0; i<6; ++i)
    {
        for(int j=0 ; j<6; ++j)
        {
            if(i==0 || i==5)
                if(j!=2 && j!=3) continue;

            if(i==1 || i==4)
                if(j!=1 && j!=4) continue;

            if(i==2 || i==3)
                if(j!=0 && j!=5) continue;

            int toss = rand()%15 + (0);
            if(toss == 0)
            {
                coins.push_back(Coin(15 + i * coin_space, y_pos + j * coin_space, COLOR_CRIMSON, true));
            }
            else 
            {
                coins.push_back(Coin(15 + i * coin_space, y_pos + j * coin_space, COLOR_GOLD, false));
            }
        }
    }
}

void set_score() {
    int score_dig[]={0,0,0,0,0,0,0,0,0,0};
    int score = player.score;
    int i=0,j=0;
    while(score != 0)
    {
        score_dig[i] = score%10;
        score /= 10;
        i++;
    }
    i=9;
    while(score_dig[i]!=0)
    {
        --i;
    }
    while(i>=0)
    {
        ssd[j].set_digit(score_dig[i]);
        --i;++j;
    }
}

void spawn_powerups() {
    if(Frame%(600/LEVEL) == 0)
    {
        powerups.push_back(PowerUp(5, 0, COLOR_CRIMSON, rand()%3));
    }
}

void spawn_fire_lines() {
    if(Frame%(400/LEVEL) == 0)
    {
        int y_pos = rand()%5 + (-2);
        fire_lines.push_back(FireLine(15, y_pos, COLOR_RED));
    }
}

void spawn_coins() {
    if(Frame%(500/LEVEL) == 0)
    {
        if(rand()%2 == 0)
            make_rectangle_coins();
        else
            make_ring_coins();
    }
}

void spawn_magnets() {
    if((Frame+1000)%(3000/LEVEL) == 0) 
    {
        if(rand()%2==0)
            magnets.push_back(Magnet(5, 3.5, COLOR_BROWN));
        else
            magnets.push_back(Magnet(5, -2, COLOR_BROWN));
    }
}

void spawn_dragons() {
    if(((Frame+1)%10000)/LEVEL == 0) 
    {
        dragons.push_back(Dragon(3, -1, COLOR_BROWN));
    }
}

void spawn_ice_balls() {
    if(dragons.size() > 0)
    {
        if(Frame % 100 == 0)
        {
            ice_balls.push_back(IceBall(dragons[0].position.x,dragons[0].position.y));
        }
    }
}

void spawn_boomerangs() {
    if(Frame%(1500/LEVEL) == 0)
    {
        int y_pos = rand()%10 + (-2);
        boomerangs.push_back(Boomerang(12, 4, COLOR_GREEN));
    }
}

void spawn_windows() {
    if(Frame%(600/LEVEL) == 0)
    // if(wall_timer.processTick())
    {

        windows.push_back(Window(15, -2.5, COLOR_GREEN));
    }
}

void spawn_tiles() {
    if(Frame%(200/LEVEL) == 0)
    {
        tiles.push_back(Tile(15, -2.7, COLOR_GREEN));
    }
}

void spawn_fire_beams() {
    if((Frame+1)%(1500/LEVEL) == 0)
    {
        fire_beams.push_back(FireBeam(-3.8, 0.8,COLOR_BLACK));
    }
}

void spawn_rings() {
    if((Frame)%(10000/LEVEL) == 0)
    {
        rings.push_back(SemiCircularRing(5, 3));
    }
}


void spawn_game_elements() {
    spawn_fire_lines();
    spawn_boomerangs();
    spawn_windows();
    spawn_tiles();
    spawn_coins();
    spawn_magnets();
    spawn_dragons();
    spawn_fire_beams();
    spawn_powerups();
    spawn_ice_balls();
    spawn_rings();
}

void level_up() {
    if(player.score > 100)
    {
        LEVEL = 2;
    }
    else if(player.score > 300)
    {
        LEVEL = 3;
    }
}


void tick_elements() {


    ground.tick();
    ring.tick();
    player.tick();
    for(int i=0;i<fire_lines.size();++i)
    {
        fire_lines[i].tick();
        if(player.immunity) fire_lines[i].danger = false;
        else fire_lines[i].danger = true;

        if(detect_line_rectangle_collision(player.bbox, fire_lines[i].line_coords) && !player.immunity && !player.ring_immune)
        {
            if(!player.immunity && !fire_lines[i].destroyed)
            {
                player.life--;
                fire_lines.erase(fire_lines.begin() + i);
            }
        }
    }
    for(int i=0;i<fire_beams.size();++i)
    {
        fire_beams[i].tick();
        if(player.immunity) 
        {
            fire_beams[i].danger = false;
            fire_beams[i].immunity = true;
        }
        else 
        {
            fire_beams[i].danger = true;
            fire_beams[i].immunity = false;
        }

        if(detect_collision(player.bbox, fire_beams[i].bbox) && !player.immunity && !fire_beams[i].destroyed && !player.ring_immune)
        {
            player.life--;
            fire_beams.erase(fire_beams.begin() + i);
        }
    }
    for(int i=0;i<magnets.size();++i)
    {
        magnets[i].tick();
        if(magnets[i].position.x < player.position.x)
        {
            player.position.x -= 2*magnets[i].gravity;
        }
        else
        {
            player.position.x += 2*magnets[i].gravity;
        }
        if(magnets[i].position.y > 0)
        {
            // player.dy += magnets[i].influence;
            player.dy -= magnets[i].influence;   

        }
        else
        {
            player.dy += magnets[i].influence;   
        }
    }
    
    for(int i=0;i<boomerangs.size();++i)
    {
        boomerangs[i].tick();
    }
    for(int i=0;i<dragons.size();++i)
    {
        dragons[i].tick();
    }
    for(int i=0;i<windows.size();++i)
    {
        windows[i].tick();
    }
    for(int i=0;i<tiles.size();++i)
    {
        tiles[i].tick();
    }
    for(int i=0;i<fuel_bullets.size();++i)
    {
        fuel_bullets[i].tick();
    }
    for(int i=0;i<water_balls.size();++i)
    {
        water_balls[i].tick();
    }
    for(int i=0;i<rings.size();++i)
    {
        rings[i].tick();
    }
    for(int i=0;i<ice_balls.size();++i)
    {
        ice_balls[i].tick();
    }
    for(int i=0;i<coins.size();++i)
    {
        coins[i].tick();
        if(player.magenetic_power)
        {
            if(coins[i].position.x > player.position.x)
            {
                coins[i].position.x -= 0.02;
            }
            else
            {
                coins[i].position.x += 0.02;
            }
            if(coins[i].position.y > player.position.y)
            {
                coins[i].position.y -= 0.02;
            }
            else
            {
                coins[i].position.y += 0.02;
            }
        }
    }
    for(int i=0;i<powerups.size();++i)
    {
        powerups[i].tick();
    }
    camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    player = Player(-3.0, 1, COLOR_BLACK);
    ground = Ground(-4, -4, COLOR_BLACK);

    

    for(int i=0;i<10;++i)
    {
        ssd.push_back(SSD(-4+i*0.2,4,COLOR_WHITE));        
    }
    for(int i=0;i<5;++i)
    {
        windows.push_back(Window(3 + i*6, -2.5, COLOR_GREEN));
        fire_lines.push_back(FireLine(3 + i*6, 2, COLOR_GREEN));
    }
    for(int i=0;i<15;++i)
    {
        tiles.push_back(Tile(3 + i*3, -2.7, COLOR_GREEN));
    }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 800;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();


            update_object_vectors();
            spawn_game_elements();

            ++Frame;
            set_score();
            level_up();
            if(player.life<0)
            {
                exit(0);
            }


            reset_screen();
            tick_input(window);

        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    // return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
    //        (abs(a.y - b.y) * 2 < (a.height + b.height));

    // If one rectangle is on left side of other 

    if (a.x > (b.x + b.width) || b.x > (a.x + a.width))
        return false; 
  
    // If one rectangle is above other 
    if (a.y < (b.y-b.height) || b.y < (a.y-a.height)) 
        return false; 
  
    return true; 
}



bool detect_line_line_collision(float p0_x, float p0_y, float p1_x, float p1_y, float p2_x, float p2_y, float p3_x, float p3_y) 
{
    float s1_x, s1_y, s2_x, s2_y;
    s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
    s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

    float s, t;
    s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
    t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        return true;
    }
    return false;
}


bool detect_line_rectangle_collision(bounding_box_t a, line_t b) 
{
    bool left = detect_line_line_collision(a.x , a.y, a.x, a.y - a.height, b.x1, b.y1, b.x2, b.y2);
    bool right = detect_line_line_collision(a.x + a.width , a.y, a.x + a.width, a.y - a.height, b.x1, b.y1, b.x2, b.y2);
    bool up = detect_line_line_collision(a.x , a.y, a.x+ a.width, a.y, b.x1, b.y1, b.x2, b.y2);
    bool down = detect_line_line_collision(a.x , a.y  - a.height, a.x+ a.width, a.y - a.height, b.x1, b.y1, b.x2, b.y2);

    if(left || right || up || down)
    {
        return true;
    }
    return false;
}



void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
