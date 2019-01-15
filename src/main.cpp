#include "main.h"
#include "timer.h"
#include "ball.h"
#include "fireline.h"
#include "player.h"
#include "boomerang.h"
#include "ground.h"
#include "tile.h"
#include "window.h"


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

long long int Frame=0;

vector<FireLine> fire_lines;
vector<Boomerang> boomerangs;
vector<Window> windows;
vector<Tile> tiles;


float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
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
    player.draw(VP);

    for(int i=0;i<fire_lines.size();++i)
    {
        fire_lines[i].draw(VP);
    }
    for(int i=0;i<boomerangs.size();++i)
    {
        boomerangs[i].draw(VP);
    }

}

void tick_input(GLFWwindow *window) {
    int left    = glfwGetKey(window, GLFW_KEY_LEFT);
    int right   = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up      = glfwGetKey(window, GLFW_KEY_UP);
    if (up) {
        player.dy -= 0.002;
    }
    cout<<player.dx;
    if(left) {
        if(player.dx == -0.01)
        {
            player.dx = 0;
        }
        else
        {
            player.dx = 0.01;
        }  
    }
    if(right) {
        if(player.dx == 0.01)
        {
            player.dx = 0;
        }
        else
        {
            player.dx = -0.01;
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
}

void spawn_fire_lines() {
    if(Frame%200 == 0)
    {
        int y_pos = rand()%10 + (-2);
        fire_lines.push_back(FireLine(5, y_pos, COLOR_RED));
    }
}

void spawn_boomerangs() {
    if(Frame%500 == 0)
    {
        int y_pos = rand()%10 + (-2);
        boomerangs.push_back(Boomerang(5, y_pos, COLOR_GREEN));
    }
}

void spawn_windows() {
    if(Frame%500 == 0)
    {

        windows.push_back(Window(5, -1.5, COLOR_GREEN));
    }
}

void spawn_tiles() {
    if(Frame%50 == 0)
    {
        int y_pos = rand()%10 + (-2);
        tiles.push_back(Tile(5, y_pos, COLOR_GREEN));
    }
}

void spawn_game_elements() {
    // spawn_fire_lines();
    // spawn_boomerangs();
    spawn_windows();
    spawn_tiles();

}


void tick_elements() {
    // ball1.tick();
    // ball2.tick();
    ground.tick();
    player.tick();
    for(int i=0;i<fire_lines.size();++i)
    {
        fire_lines[i].tick();
    }
    for(int i=0;i<boomerangs.size();++i)
    {
        boomerangs[i].tick();
    }
    for(int i=0;i<windows.size();++i)
    {
        windows[i].tick();
    }
    for(int i=0;i<tiles.size();++i)
    {
        tiles[i].tick();
    }
    camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    player = Player(0, 0, COLOR_BLACK);
    ground = Ground(-4, -4, COLOR_BLACK);
    windows.push_back(Window(0, -1.5, COLOR_GREEN));
    // ball1       = FireLine(0, 0, COLOR_RED);
    // ball2       = FireLine(0.5, 0.5, COLOR_GREEN);
    // fire_lines.push_back(FireLine(0, 0, COLOR_RED));
    // fire_lines.push_back(FireLine(0.5, 0.5, COLOR_GREEN));
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
    int width  = 1000;
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

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
