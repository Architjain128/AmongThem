#include "main.h"
#include "timer.h"
#include "ball.h"
#include "maze.h"
#include "body.h"
#include "square.h"
#include "Kruskal.h"
#include "Transversal.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
Kruskal myMaze = Kruskal(8);
Transversal myTran = Transversal();
int **Map,**TransMap,mazeSize=8;
int xPlayer,yPlayer,xEnemy,yEnemy,playerType=0;
int inDoor,outDoor,xNim,yNim,rotBy=1;
int xNim1,yNim1;
float xRot=-20,yRot,xNimRot,yNimRot,zNimRot;
int viewMode = 0;
bool isTrans,isMorning=true,isEnemyrun=true;
bool diff = false, spec = false, amb = false;
float pos[] = {1,10.5,0};
float ver[] = {0,-1,0};
float alpha = 4.71;
int xRoad,yRoad;
float l=-1.5,b=-4.0,t=1.0,r=4.5;
/**************************
* Customizable functions *
**************************/
// Square mazzze[200];
Square bg ;
Ball ball1;
Body player;
Maze mazze;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);



void placeDoor() {
        inDoor = myMaze.getDorPos();
        outDoor = myMaze.getDorPos();
        Map[0][inDoor] = 0;
        Map[myMaze.getLength()*2][outDoor] = 0;
}
void settingUp(int size){
        myMaze = Kruskal(size);
        myMaze.doGenerate();
        Map = myMaze.getMap();
        xNim = (rand() % myMaze.getLength())*2+1;    // button x
        yNim = (rand() % myMaze.getLength())*2+1;    // button y
        xNim1 = (rand() % myMaze.getLength())*2+1;    // button x
        yNim1 = (rand() % myMaze.getLength())*2+1;    // button y
        placeDoor();
        myTran = Transversal(myMaze.getMap(),mazeSize*2+1,size*2-1,size*2-1,inDoor);
        myTran.doTransit();
        TransMap = myTran.getMap();
        pos[1] = size + 2.5;
        size % 2 == 0 ? pos[0] = 1 : pos[0] = 0;
        xPlayer=outDoor; yPlayer=myMaze.getLength()*2;
        myMaze.print_array();
        // return;
        xEnemy=size*2-1; yEnemy=size*2-1;
}



/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    mazze.draw(VP);
    bg.draw(VP);
    player.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    if (left) {
        // Do something
    }
}

void tick_elements() {
    // ball1.tick();
    // camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1 = Ball(0, 0, COLOR_RED);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("../source/shaders/shader.vert", "../source/shaders/shader.frag");
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
    int width  = 720;
    int height = 840;
    settingUp(8);
    
    window = initGLFW(width, height);

    initGL (window, width, height);

    int sqt=0;
    for (int i = 0; i < myMaze.getSize(); i++) {
        for (int j = 0; j < myMaze.getSize(); j++) {
            if (Map[i][j]==1) {
                    sqt++;
            }
        }
    }

    GLfloat mazevertex[18*sqt];
    int bbb=0;
    for (int i = 0; i < myMaze.getSize(); i++) {
        for (int j = 0; j < myMaze.getSize(); j++) {
            if (Map[i][j]==1) {
                mazevertex[bbb*3+0]=i;
                mazevertex[bbb*3+1]=j;
                mazevertex[bbb*3+2]=0;
                bbb++;
                mazevertex[bbb*3+0]=i;
                mazevertex[bbb*3+1]=j+1;
                mazevertex[bbb*3+2]=0;
                bbb++;
                mazevertex[bbb*3+0]=i+1;
                mazevertex[bbb*3+1]=j+1;
                mazevertex[bbb*3+2]=0;
                bbb++;
                mazevertex[bbb*3+0]=i+1;
                mazevertex[bbb*3+1]=j+1;
                mazevertex[bbb*3+2]=0;
                bbb++;
                mazevertex[bbb*3+0]=i;
                mazevertex[bbb*3+1]=j;
                mazevertex[bbb*3+2]=0;
                bbb++;
                mazevertex[bbb*3+0]=i+1;
                mazevertex[bbb*3+1]=j;
                mazevertex[bbb*3+2]=0;
                bbb++;
            }
        }
    }
    bg = Square(l,r,t,b,-0.1,0.6,0.6,0.6);
    
    mazze = Maze(0,0,0.1,mazevertex,bbb,l,r,t,b);
    player = Body(0,0,l,r,t,b,0.1,0,0,1);
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
