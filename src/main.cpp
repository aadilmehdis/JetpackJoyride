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


#include <vector>

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

FireLine ball1;
FireLine ball2;
Player player;
Ground ground;
Dragon dragon;

long long int Frame=0;

vector<FireLine> fire_lines;
vector<Boomerang> boomerangs;
vector<Window> windows;
vector<Tile> tiles;
vector<FuelBullet> fuel_bullets;
vector<Coin> coins;


float screen_zoom = 1.0, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

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
    for(int i=0;i<fire_lines.size();++i)
    {
        fire_lines[i].draw(VP);
    }
    for(int i=0;i<boomerangs.size();++i)
    {
        boomerangs[i].draw(VP);
    }
    for(int i=0; i<fuel_bullets.size(); ++i)
    {
        fuel_bullets[i].draw(VP);
    }
    for(int i=0; i<coins.size(); ++i)
    {
        coins[i].draw(VP);
    }
    player.draw(VP);
    dragon.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left    = glfwGetKey(window, GLFW_KEY_LEFT);

    int right   = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up      = glfwGetKey(window, GLFW_KEY_UP);
    if (up) {
        player.dy -= 0.005;
        if(Frame%10 == 0)
        {
            fuel_bullets.push_back(FuelBullet(player.position.x-0.3, player.position.y-0.6, COLOR_GOLD));
        }
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
                // fire_lines[i].dx += player.dx;
                fire_lines[i].dx = 2*player.dx;

            } 
            for(int i=0;i<boomerangs.size();++i)
            {
                // boomerangs[i].dx = player.dx;
                // boomerangs[i].dx = 2*player.dx;
            }  
            for(int i=0;i<windows.size();++i)
            {
                // windows[i].dx += player.dx;
                windows[i].dx = 2*player.dx;
            }
            for(int i=0;i<tiles.size();++i)
            {
                // tiles[i].dx += player.dx;
                tiles[i].dx = 2*player.dx;
            } 
            for(int i=0;i<coins.size();++i)
            {
                // coins[i].dx += player.dx;
                coins[i].dx = 2*player.dx;
            } 
        }
    }
}

void update_object_vectors() {
    for(int i=0;i<fire_lines.size();++i)
    {
        if(fire_lines[i].position.x < -5)
        {
            fire_lines.erase(fire_lines.begin() + i);
        }
    } 
    for(int i=0;i<boomerangs.size();++i)
    {
        if(boomerangs[i].position.x < -5)
        {
            boomerangs.erase(boomerangs.begin() + i );
        }
    }  
    for(int i=0;i<windows.size();++i)
    {
        if(windows[i].position.x < -15)
        {
            windows.erase(windows.begin() + i );
        }
    }
    for(int i=0;i<tiles.size();++i)
    {
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
    for(int i=0;i<coins.size();++i)
    {
        if(coins[i].position.y < -2.5)
        {
            coins.erase(coins.begin() + i );
        }

        //check for collision here itself for collecting coins. and erasing them.
    }
}

void make_rectangle_coins() {
    float coin_space = 0.21;
    int y_pos = rand()%4 + (0);
    for(int i=0; i<9; ++i)
    {
        for(int j=0 ; j<3; ++j)
        {
            int toss = rand()%15 + (0);
            if(toss == 0)
            {
                coins.push_back(Coin(5 + i * coin_space, y_pos + j * coin_space, COLOR_CRIMSON, true));
            }
            else 
            {
                coins.push_back(Coin(5 + i * coin_space, y_pos + j * coin_space, COLOR_GOLD, false));
            }
        }
    }
}



void spawn_fire_lines() {
    if(Frame%200 == 0)
    {
        int y_pos = rand()%10 + (-2);
        fire_lines.push_back(FireLine(5, y_pos, COLOR_RED));
    }
}

void spawn_coins() {
    if(Frame%250 == 0)
    {
        make_rectangle_coins();
        // int y_pos = rand()%4 + (0);
        // if(Frame % 500 == 0)
        // {
        //     coins.push_back(Coin(5, y_pos, COLOR_CRIMSON, true));
        //     coins.push_back(Coin(5.38, y_pos, COLOR_CRIMSON, true));


        // }
        // else 
        // {
        //     coins.push_back(Coin(5, y_pos, COLOR_GOLD, false));
        // }
    }
}


void spawn_boomerangs() {
    if(Frame%1500 == 0)
    {
        int y_pos = rand()%10 + (-2);
        // boomerangs.push_back(Boomerang(5, y_pos, COLOR_GREEN));
        boomerangs.push_back(Boomerang(12, 4, COLOR_GREEN));
    }
}

void spawn_windows() {
    if(Frame%500 == 0)
    {

        windows.push_back(Window(5, -1.5, COLOR_GREEN));
    }
}

void spawn_tiles() {
    if(Frame%200 == 0)
    {
        tiles.push_back(Tile(5, -2.7, COLOR_GREEN));
    }
}

void spawn_game_elements() {
    spawn_fire_lines();
    spawn_boomerangs();
    spawn_windows();
    spawn_tiles();
    spawn_coins();
}


void tick_elements() {
    // ball1.tick();
    // ball2.tick();
    dragon.tick();
    ground.tick();
    player.tick();
    cout<<"Player bbox \n x : "<<player.bbox.x<<"\n y : "<<player.bbox.y<<"\n x2 : "<<player.bbox.x+player.bbox.width<<"\n y2 : "<<player.bbox.y-player.bbox.height<<"\n";
    for(int i=0;i<fire_lines.size();++i)
    {
        fire_lines[i].tick();

        if(detect_line_rectangle_collision(player.bbox, fire_lines[i].line_coords))
        {
            cout<<"Collision\n";
        }
        else{
            cout<<"No Collision\n";
        }
    }
    for(int i=0;i<boomerangs.size();++i)
    {
        // boomerangs[i].tick();
    }
    for(int i=0;i<windows.size();++i)
    {
        // windows[i].tick();
    }
    for(int i=0;i<tiles.size();++i)
    {
        // tiles[i].tick();
    }
    for(int i=0;i<fuel_bullets.size();++i)
    {
        // fuel_bullets[i].tick();
    }
    for(int i=0;i<coins.size();++i)
    {
        // coins[i].tick();
    }
    camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    player = Player(-3.0, 0, COLOR_BLACK);
    ground = Ground(-4, -4, COLOR_BLACK);
    dragon = Dragon(2,10,COLOR_BLACK);
    windows.push_back(Window(0, -1.5, COLOR_GREEN));

    // tiles.push_back(Tile(-4, -3.5, COLOR_GREEN));
    // tiles.push_back(Tile(-2.5, -3.5, COLOR_GREEN));
    // tiles.push_back(Tile(-1, -3.5, COLOR_GREEN));
    // tiles.push_back(Tile(1.5, -3.5, COLOR_GREEN));

    // ball1       = FireLine(0, 0, COLOR_RED);
    // ball2       = FireLine(0.5, 0.5, COLOR_GREEN);
    fire_lines.push_back(FireLine(-2, 0, COLOR_RED));
    // fire_lines.push_back(FireLine(-1, -1, COLOR_GREEN));
    // fire_lines.push_back(FireLine(1, 1, COLOR_BLACK));

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


            tick_input(window);

        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
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
        cout<<"left : "<<left<<endl;
        cout<<"right : "<<right<<endl;
        cout<<"up : "<<up<<endl;
        cout<<"down : "<<down<<endl;
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
