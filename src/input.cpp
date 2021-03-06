#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "main.h"
#include "window.h"
#include "fireline.h"
#include "tile.h"
#include "boomerang.h"
#include "coin.h"
#include "magnet.h"
#include "semicircularring.h"

bool   cannon_keyboard_input = true;
bool   drag_pan = false, old_cki;
double drag_oldx = -1, drag_oldy = -1;

extern std::vector<Window> windows;
extern std::vector<Boomerang> boomerangs;
extern std::vector<Tile> tiles;
extern std::vector<FireLine> fire_lines;
extern std::vector<Coin> coins;
extern std::vector<Magnet> magnets;
extern std::vector<SemiCircularRing> rings;

extern float screen_zoom;


using namespace std;

/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Function is called first on GLFW_PRESS.

    if (action == GLFW_RELEASE) {
            for(int i=0;i<fire_lines.size();++i)
            {
                fire_lines[i].dx = 0.01;
            } 
            // for(int i=0;i<boomerangs.size();++i)
            // {
            //     boomerangs[i].dx = 0.01;
            // }  
            for(int i=0;i<windows.size();++i)
            {
                windows[i].dx = 0.01;
            }
            for(int i=0;i<tiles.size();++i)
            {
                tiles[i].dx = 0.01;
            }
            for(int i=0;i<coins.size();++i)
            {
                coins[i].dx = 0.01;
            }  
            for(int i=0;i<magnets.size();++i)
            {
                magnets[i].dx = 0.01;
            }  
            for(int i=0;i<rings.size();++i)
            {
                rings[i].dx = 0.01;
            }  
        // switch (key) {
        // case GLFW_KEY_C:
        // rectangle_rot_status = !rectangle_rot_status;
        // break;
        // case GLFW_KEY_P:
        // triangle_rot_status = !triangle_rot_status;
        // break;
        // case GLFW_KEY_X:
        //// do something ..
        // break;
        // default:
        // break;
        // }
    } else if (action == GLFW_PRESS) {
        switch (key) {
        case GLFW_KEY_ESCAPE:
            quit(window);
            break;
        default:
            break;
        }
    }
}

/* Executed for character input (like in text boxes) */
void keyboardChar(GLFWwindow *window, unsigned int key) {
    switch (key) {
    case 'Q':
    case 'q':
        quit(window);
        break;
    default:
        break;
    }
}

/* Executed when a mouse button is pressed/released */
void mouseButton(GLFWwindow *window, int button, int action, int mods) {
    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
        if (action == GLFW_PRESS) {
            // Do something
            return;
        } else if (action == GLFW_RELEASE) {
            // Do something
        }
        break;
    // case GLFW_MOUSE_BUTTON_RIGHT:
    // if (action == GLFW_RELEASE) {
    // rectangle_rot_dir *= -1;
    // }
    // break;
    default:
        break;
    }
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    // Do something
    if(yoffset < 0)
    {
        if(screen_zoom < 1.3)
        {
            screen_zoom += 0.01;
        }
    }
    else if(yoffset > 0)
    {
        if(screen_zoom > 1.0)
        {
            screen_zoom -= 0.01;
        }
    }
}
