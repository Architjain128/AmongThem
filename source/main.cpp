#include "main.h"
#include "timer.h"
#include "ball.h"
#include "maze.h"
#include "gate.h"
#include "body.h"
#include "boomer.h"
#include "vaporize.h"
#include "square.h"
#include "Kruskal.h"
#include "Transversal.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
Kruskal myMaze = Kruskal(8);
Transversal myTran = Transversal();
int Battery = 10;
int Points = 0;
int Health = 100;
int Pause = 0;
int **Map,**TransMap,mazeSize=8;
int xPlayer,yPlayer,xEnemy,yEnemy,playerType=0;
int xPlay,yPlay,changePlay=0;
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
int boom1=1,xboom1,yboom1;
int boom2=1,xboom2,yboom2;
int boom3=1,xboom3,yboom3;
int vap1=1,xvap1,yvap1;

/**************************
* Customizable functions *
**************************/
// Square mazzze[200];
Square bg ;
Gate endd ;
Boomer boomerang1;
Boomer boomerang2;
Boomer boomerang3;
Vaporize vaporize1;
Body player;
Body imposter;
Maze mazze;
vector<pair<int,int>> vv;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
Timer t60(1.0/30);
int cc,dd;
bool checkobj(int a,int b){
    if(a<0 || b<0)
    return false;
    if(a>mazeSize*2 || b>mazeSize*2)
    return false;
    if(Map[a][16-b]==1)
    return false;
    for(int i=0;i<vv.size();i++)
    {
        if(vv[i].first == a && vv[i].second == b)
        return false;
    }
    return true;
}

bool checkpath(int a,int b){
    
    if(a<0 || b<0)
    return false;
    if(a>mazeSize*2 || b>mazeSize*2)
    return false;
    if(Map[a][16-b]==1)
    return false;

    if((a==xboom1 && b==yboom1 && boom1==1))
    {
        boom1=0;
        Points +=100;
    }
    if((a==xboom2 && b==yboom2 && boom2==1))
    {
        boom2=0;
        Points +=100;
    }
    if((a==xboom3 && b==yboom3 && boom3==1))
    {
        boom3=0;
        Points -=40;
    }
    if((a==xvap1 && b==yvap1 && vap1==1))
    {
        vap1=0;
        Points+=150;
        // Points -=40;
    }

    return true;
}

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
        while(1){
            cc = (rand() % myMaze.getLength())*2+1;    // button x
            dd = 16-(rand() % myMaze.getLength())*2+1;    // button y
            if(checkobj(cc,dd)==true){
                xboom1 = cc;
                yboom1 = dd;
                vv.push_back(make_pair(cc,dd));
                break;
            }
        }
        while(1){
            cc = (rand() % myMaze.getLength())*2+1;    // button x
            dd = 16-(rand() % myMaze.getLength())*2+1;    // button y
            if(checkobj(cc,dd)==true){
                xboom2 = cc;
                yboom2 = dd;
                vv.push_back(make_pair(cc,dd));
                break;
            }
        }
        while(1){
            cc = (rand() % myMaze.getLength())*2+1;    // button x
            dd = 16-(rand() % myMaze.getLength())*2+1;    // button y
            if(checkobj(cc,dd)==true){
                xboom3 = cc;
                yboom3 = dd;
                vv.push_back(make_pair(cc,dd));
                break;
            }
        }
        while(1){
            cc = (rand() % myMaze.getLength())*2+1;    // button x
            dd = 16-(rand() % myMaze.getLength())*2+1;    // button y
            if(checkobj(cc,dd)==true){
                xvap1 = cc;
                yvap1 = dd;
                vv.push_back(make_pair(cc,dd));
                break;
            }
        }

        placeDoor();
        myTran = Transversal(myMaze.getMap(),mazeSize*2+1,size*2-1,size*2-1,inDoor);
        myTran.doTransit();
        TransMap = myTran.getMap();
        pos[1] = size + 2.5;
        size % 2 == 0 ? pos[0] = 1 : pos[0] = 0;
        xPlayer=inDoor; 
        yPlayer=16;
        
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
    if(boom1==1)
    boomerang1.draw(VP);
    if(boom2==1)
    boomerang2.draw(VP);
    if(boom3==1)
    boomerang3.draw(VP);
    if(vap1==1){
        vaporize1.draw(VP);
        imposter.draw(VP);
    }
    if(Points<150){
        endd.draw(VP);
    }
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    if (left) {
        if(checkpath(xPlay-1,yPlay)){
            xPlay-=1;
            changePlay=1;
        }
    }
    if (right) {
        if(checkpath(xPlay+1,yPlay)){
            xPlay+=1;
            changePlay=1;
        }
    }
    if (up) {
        if(checkpath(xPlay,yPlay-1)){
            yPlay-=1;
            changePlay=1;
        }
    }
    if (down) {
        if(checkpath(xPlay,yPlay+1)){
            yPlay+=1;
            changePlay=1;
        }
    }
    if(space){
        cout<<player.position.x<<" "<<player.position.y<<endl;
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

    // ball1 = Ball(0, 0, COLOR_RED);

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
    bg = Square(l,r,t,b,-0.1,0.6,0.6,0.6,COLOR_BLACK);
    mazze = Maze(0,0,0.1,mazevertex,bbb,l,r,t,b);
    xPlay = 0;
    yPlay = 7;
    player = Body(xPlay,yPlay,l,r,t,b,0.2,76.0/256.0,64.0/256.0,245.0/256.0);
    imposter = Body(15,yPlay,l,r,t,b,0.2,253.0/256.0,52.0/256.0,171.0/256.0);
    boomerang1 = Boomer(xboom1,yboom1,l,r,t,b,0.3,0,0,0,1);
    boomerang2 = Boomer(xboom2,yboom2,l,r,t,b,0.3,0,0,0,1);
    boomerang3 = Boomer(xboom3,yboom3,l,r,t,b,0.3,0,0,0,0);
    vaporize1 = Vaporize(xvap1,yvap1,l,r,t,b,0.3,0,0,0,0);
    endd = Gate(16,7,l,r,t,b,0.3,0,0,0,0);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers
        if(changePlay==1){
            changePlay=0;
            player = Body(xPlay,yPlay,l,r,t,b,0.2,76.0/256.0,64.0/256.0,245.0/256.0);
        }
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
