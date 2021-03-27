#include "main.h"
#include "timer.h"
#include "ball.h"
#include "square.h"
#include "body.h"
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
bool is_Trans,is_light = true,is_imposter=true;
bool diff = false, spec = false, amb = false;
float pos[] = {1,10.5,0};
float ver[] = {0,-1,0};
float alpha = 4.71;
int xRoad,yRoad;
bool mazze_flag = true;
Square mazze[2000]; 
Square vapouriser;
Body body1;
Body body2;
Ball ball1;
int bb = 1;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
Timer t60(1.0/60);

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
        // myMaze.print_array();
        // return;
        xEnemy=size*2-1; yEnemy=size*2-1;
}

void pseudo_display(){
    is_light == true ? glClearColor(0.5,0.5,1,0.5) : glClearColor(0.0,0.0,0.0,1);
    glLoadIdentity();
    glOrtho(-mazeSize-2.5, mazeSize+2.5, -mazeSize-2.5, mazeSize+2.5, -mazeSize-4.5, mazeSize+4.5);
    glMatrixMode(GL_MODELVIEW);

    glShadeModel(GL_FLAT);
    //tranparanceDependeci
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
}

void drawBoxes(float z1,float z2,float left,float down,float right,float top,float r,float g,float b,float d,int bb) {
    
    mazze[bb]=Square(left,right,top,down,z1,r,g,b);
    // mazze[bb+1]=Square(left,right,top,down,z2,r,g,b);
    // mazze[bb+2]=Square(left,right,top,down,z2,r+0.2,g+0.2,b+0.2);
    // mazze[bb+3]=Square(left,right,top,down,z2,r+0.2,g+0.2,b+0.2);
    // mazze[bb+4]=Square(left,right,top,down,z2,r+0.2,g+0.2,b+0.2);
    // mazze[bb+5]=Square(left,right,top,down,z2,r+0.2,g+0.2,b+0.2);


}

void setDisplay(){
        //TODO: seting up ctm display only
        glPushMatrix();
        glTranslatef(mazeSize+0.5,mazeSize+0.5,0);
        // if (viewMode==1) {
        //         glRotatef(yRot,0,1,0);
        //         glRotatef(xRot,1,0,0);
        // }
        glTranslatef(-mazeSize-0.5,-mazeSize-0.5,0);
}
void putMaterial(float r,float g,float b, float a) {
        GLfloat mat_specular[] = { r, g, b, a };
        GLfloat mat_shininess[] = { 10.0 };
        GLfloat mat_diffuse[] = { r, g, b, a };
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
}

void setvaporizer() {
        //TODO: seting up ctm nim only
        putMaterial(1.0, 0.0, 0.0, 1.0);
        glPushMatrix();
        if (viewMode!=0) {
                glTranslated(0.5+xNim,0.5+yNim,0);
                glRotatef(xNimRot,1,0,0);
                glRotatef(yNimRot,0,1,0);
                glRotatef(zNimRot,0,0,1);
                //glScalef(0.8,0.8,1);
                glTranslated(-0.5-xNim,-0.5-yNim,0);
        }
        // drawNim();
        vapouriser=Square(xNim,yNim,xNim+1,yNim+1,0.1,0.1,0.1,0.1);
        glPopMatrix();
}

void setplayer(){
    putMaterial(0.0, 1.0, 0.0, 1.0);
        glPushMatrix();
        // glTranslatef(xPlayer+0.5,yPlayer+0.5,0);
        body1 = Body(0,0,-2,-1,1,-1, 0,1,0,1);

        glPopMatrix();
}
void setimposter(){
    putMaterial(0.0, 1.0, 0.0, 1.0);
        glPushMatrix();
        // glTranslatef(xPlayer+0.5,yPlayer+0.5,0);
        body2 = Body(0,0,-2,-1,1,-1, 0,1,0,0);

        glPopMatrix();
}
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    pseudo_display();

    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // setDisplay();
    
    // is_Trans == true ? putMaterial(0.0,0.0,0.8,0.3) : putMaterial(0.0,0.0,0.8,1.0);
    // if(mazze_flag == true){
    // for (int i = 0; i < myMaze.getSize(); i++) {
    //         for (int j = 0; j < myMaze.getSize(); j++) {
    //                 if (Map[i][j]==1) {
    //                     mazze[bb]=Square(j,i,j+1,i+1,0.5,0.1,0.1,0.1);
    //                     bb++;
    //                 }
    //         }
    // }
    // mazze_flag = false;
    // }
    // // setvaporizer();
    // // setplayer();
    // // setimposter();

    // putMaterial(1, 1, 1, 0.5);
    // mazze[0] = Square(0,0,mazeSize*2+1,mazeSize*2+1,-0.51,0.6,0.6,0.6);
    // // drawBox(-0.51,-0.61,0,0,mazeSize*2+1,mazeSize*2+1,0.6,0.6,0.6,0.4);
    glPopMatrix();
    glfwSwapBuffers(window);



    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 1, 11, 0);
    // // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (1, 10, 0);
    // // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 0, 1);

    // // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D

    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane
    Matrices.view = glm::ortho(-mazeSize-2.5, mazeSize+2.5, -mazeSize-2.5, mazeSize+2.5, -mazeSize-4.5, mazeSize+4.5);

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model


    // display();


    // Scene render
    // ball1.draw(VP);
    // square.draw(VP);
    // square1.draw(VP);
    // body1.draw(VP);
    // body2.draw(VP);
    mazze[0].draw(VP);
    // for(int i=0;i<bb;i++)mazze[i].draw(VP);

}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int down  = glfwGetKey(window, GLFW_KEY_DOWN);
    int up  = glfwGetKey(window, GLFW_KEY_UP);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    if(left){
        body1.position.x-=.01;
    }
    if(right){
        body1.position.x+=.01;
    }
    if(up){
        body1.position.y+=.01;
    }
    if(down){
        body1.position.y-=.01;
    }
}

void tick_elements() {
    // ball1.tick();
    // square.tick();
    body1.tick();
    // camera_rotation_angle = M_PI/2;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1 = Ball(0, 0, COLOR_RED);
    // square = Square(-1,1,1,-1, 0, COLOR_RED);
    // square1 = Square(-2,-1,1,-1, 0, COLOR_BLACK);
    mazze[0] = Square(0,0,mazeSize*2+1,mazeSize*2+1,-0.51,0.6,0.6,0.6);
    
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
    int width  = 500;
    int height = 500;
    settingUp(8);

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
