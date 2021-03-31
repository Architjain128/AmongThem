#include "main.h"
#include "timer.h"
#include "ball.h"
#include "maze.h"
#include "gate.h"
#include "body.h"
#include "board.h"
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
int xPlay2,yPlay2,changePlay2=0;
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
int vap2=1,xvap2,yvap2;
int desired_points = 300;
int Map2[17][17]={0};
int bfsmap[290][17][17];
int vis[290][17][17];
int inf = 1000000000;
int TOTIME = 60;
float hx=0,hy=0,hz=1.0;
int mmm=1;
/**************************
* Customizable functions *
**************************/
// Square mazzze[200];
Square bg ;
Gate endd ;
Gate endd1 ;
Boomer boomerang1;
Boomer boomerang2;
Boomer boomerang3;
Vaporize vaporize1;
Vaporize vaporize2;
Body player;
Body imposter;
Maze mazze;
Board win;
Board loss;
vector<pair<int,int>> vv;
vector<pair<int,int>> path;
vector<pair<int,int>> graph[17][17];
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
Timer t60(1.0/20);
Timer t1(1.0);
string status="op";
int Tasks=0;
int cc,dd;

// void glutBitmapCharacter()
// glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*c);

// void displayText(float x, float y, float z, char *string) {
// 	glColor3f(255.0/255.0, 37.0/255.0, 0);
//     cout<<"prpripri"<<endl;
//     glRasterPos3f(x, y, z);
// 	for (char* c = string; *c != '\0'; c++) {
// 		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);  // Updates the position
// 	}
// }

bool checkk(int a,int b){
    if(a<0||b<0||a>16||b>16)return false;
    if(Map2[a][b]==1)return false;
    return true;
}

void hipster(){
    for (int  i = 0; i < 17; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            if(Map[i][j]==1)
            Map2[i][16-j]=Map[i][j];
        }
    }
}

void bfs(int id){
    int a=id/17,b=id%17;
    bfsmap[id][a][b]=0;

    queue<int> q;
    q.push(id);

    while (q.empty()!=1)
    {
        // cout<<id<<" "<<q.size()<<endl;
        int i=q.front()/17;
        int j=q.front()%17;
        q.pop();
        // if(q.size()>10) break;
        if(checkk(i-1,j)&& vis[id][i-1][j]==0){
            q.push((i-1)*17+j);
            vis[id][i-1][j]=1;
            bfsmap[id][i-1][j]=min(bfsmap[id][i-1][j],bfsmap[id][i][j]+1);
        }
        if(checkk(i+1,j) && vis[id][i+1][j]==0){
            q.push((i+1)*17+j);
            vis[id][i+1][j]=1;
            bfsmap[id][i+1][j]=min(bfsmap[id][i+1][j],bfsmap[id][i][j]+1);
        }
        if(checkk(i,j-1)&& vis[id][i][j-1]==0){
            q.push((i*17+j-1));
            vis[id][i][j-1]=1;
            bfsmap[id][i][j-1]=min(bfsmap[id][i][j-1],bfsmap[id][i][j]+1);
        }
        if(checkk(i,j+1) && vis[id][i][j+1]==0){
            q.push((i*17+j+1));
            vis[id][i][j+1]=1;
            bfsmap[id][i][j+1]=min(bfsmap[id][i][j+1],bfsmap[id][i][j]+1);
        }
    }
    


}

void BFS(){
    for (int i = 0; i < 17; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            if(Map2[i][j]!=1){
                for (int i1 = 0; i1 < 17; i1++)
                {
                    for (int j1 = 0; j1 < 17; j1++)
                    {
                        bfsmap[i*17+j][i1][j1]=inf;
                        vis[i*17+j][i1][j1]=0;
                    }
                }
                bfs(i*17+j);
            }
        }
        // cout<<i<<endl;
    }
    
}

int heavy_driver(){
    int a2 = xPlay2;
    int b2 = yPlay2;
    int a1 = xPlay;
    int b1 = yPlay;
    int z1 = 17*a1+b1;
    int z2 = 17*a2+b2;
    int res=0;
    int dd = bfsmap[z1][a2][b2];
    if(a2-1>=0){
        if(dd>bfsmap[z1][a2-1][b2])
        {
            dd = bfsmap[z1][a2-1][b2];
            res = 1;
        }
            // cout<<a2-1<<" "<<b2<<" "<<bfsmap[z1][a2-1][b2]<<endl;
    }
    if(a2+1<17){
        if(dd>bfsmap[z1][a2+1][b2]){
            dd = bfsmap[z1][a2+1][b2];
            res=2;
        }
            // cout<<a2+1<<" "<<b2<<" "<<bfsmap[z1][a2+1][b2]<<endl;
    }
    if(b2-1>=0){
        if(dd>bfsmap[z1][a2][b2-1]){
            dd=bfsmap[z1][a2][b2-1];
            res=3;
        }
            // cout<<a2<<" "<<b2-1<<" "<<bfsmap[z1][a2][b2-1]<<endl;
    }
    if(b2+1<17){
        if(dd>bfsmap[z1][a2][b2+1]){
            dd = bfsmap[z1][a2][b2+1];
            res = 4;
        }
            // cout<<a2<<" "<<b2+1<<" "<<bfsmap[z1][a2][b2+1]<<endl;
    }
    // cout<<a2<<" "<<b2<<"_ "<<bfsmap[z1][a2][b2]<<endl;
    

    // if( (a2-1>=0 && a2-1<17) &&  bfsmap[z1][a2-1][b2]< dd)
    // {
    //     res=1;
    //     int dd = bfsmap[z1][a2-1][b2];
    // }
    // if( (a2+1>=0 && a2+1<17) && bfsmap[z1][a2+1][b2]< dd)
    // {
    //     res=2;
    //     int dd = bfsmap[z1][a2+1][b2];
    // }
    // if( (b2-1>=0 && b2-1<17) &&  bfsmap[z1][a2][b2-1]< dd)
    // {
    //     res=3;
    //     int dd = bfsmap[z1][a2][b2-1];
    // }
    // if( (z2+17>=0 && z2+17<289) &&  bfsmap[z1][a2][b2+1]< dd)
    // {
    //     res=4;
    //     int dd = bfsmap[z1][a2][b2+1];
    // }
    // cout<<res<<" "<<bfsmap[z1][a2][b2]<<" "<<a2<<" "<<b2<<endl;
    return res;
}

bool checky(int a,int b){
    if(a<0||b<0)return false;
    if(a>16||b<16)return false;
    return true;
}

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
    if(a==0 && b==7) return false;
    if(a==16 && b==7){
        if(Points>=desired_points)
        return true;
        else{
        // cout<<"colloectpoint"<<endl;
        return false;
        }
    }

    if((a==xboom1 && b==yboom1 && boom1==1 && vap2==0))
    {
        boom1=0;
        Points +=100;
    }
    if((a==xboom2 && b==yboom2 && boom2==1 && vap2==0))
    {
        boom2=0;
        Points +=100;
    }
    if((a==xboom3 && b==yboom3 && boom3==1 && vap2==0))
    {
        boom3=0;
        Points -=100;
    }
    if((a==xvap1 && b==yvap1 && vap1==1))
    {
        vap1=0;
        Tasks++;
        Points+=150;
    }
    if((a==xvap2 && b==yvap2 && vap2==1))
    {
        vap2=0;
        Tasks++;
        Points+=150;
    }
    if((xPlay==xPlay2 && yPlay==yPlay2 && vap1==1))
    {
        status="GAME OVER";
    }
    if(xPlay==16 && yPlay==7 && Tasks>=2 && Points>=desired_points){
        status="YOU WON";
    }
    if(TOTIME<0){
        status="GAME OVER";
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
        while(1){
            cc = (rand() % myMaze.getLength())*2+1;    // button x
            dd = 16-(rand() % myMaze.getLength())*2+1;    // button y
            if(checkobj(cc,dd)==true){
                xvap2 = cc;
                yvap2 = dd;
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
        
        // myMaze.print_array();
        // // return;
        xEnemy=size*2-1; yEnemy=size*2-1;
}

void msg_TO_HUD(){
    
    cout <<"=================================================="<<endl;
    cout<<"||\t\tPoints : "<<Points<<"\t\t\t||"<<endl;
    cout<<"||\t\tLight : ON"<<"\t\t\t||"<<endl;
    cout<<"||\t\tTasks : "<<Tasks<<"/2"<<"\t\t\t||"<<endl;
    cout<<"||\t\tTime Remaining : "<< TOTIME<<"\t\t||"<<endl;
    cout <<"=================================================="<<endl<<endl;
    if(status!="op"){
        if(status=="GAME OVER")
    cout << "\t\t\033[1;31m"<<status<<"\033[0m\n"<<endl;
            if(status=="YOU WON")
    cout << "\t\t\033[1;34m"<<status<<"\033[0m\n"<<endl;
    mmm=0;
    cout<<"Press Q to exit"<<endl;
    }
    cout<<endl<<endl;
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
    endd1.draw(VP);

    if(status=="op"){
    player.draw(VP);
    if(vap2==0){
        if(boom1==1)
        boomerang1.draw(VP);
        if(boom2==1)
        boomerang2.draw(VP);
        if(boom3==1)
        boomerang3.draw(VP);
    }
    if(vap1==1){
        vaporize1.draw(VP);
        imposter.draw(VP);
    }
    if(vap2==1){
        vaporize2.draw(VP);
        // imposter.draw(VP);
    }
    if(Points<desired_points){
        endd.draw(VP);
    }
    }
    if(status=="GAME OVER")loss.draw(VP);
    if(status=="YOU WON")win.draw(VP);

}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int Q = glfwGetKey(window,GLFW_KEY_Q);
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
        // cout<<player.position.x<<" "<<player.position.y<<endl;
    }
    if(Q){
        glfwSetWindowShouldClose(window, true);
    }
    // if(glfwGetKey(window, GLFW_KEY_Z)){
    //     hx+=1.0;
    //     // cout<<"x+"<<endl;
    // }
    // if(glfwGetKey(window, GLFW_KEY_X)){
    //     hx-=1.0;
    //     cout<<"x-"<<endl;
    // }
    // if(glfwGetKey(window, GLFW_KEY_C)){
    //     hy+=1.0;
    //     cout<<"y+"<<endl;
    // }
    // if(glfwGetKey(window, GLFW_KEY_V)){
    //     hy-=1.0;
    //     cout<<"y-"<<endl;
    // }

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
    hipster();
    BFS();

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
    xPlay = 1;
    yPlay = 7;
    xPlay2 = 15;
    yPlay2 = 7;


    // move_imposter(15,7,16,7);
    // cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
    // for (int i = 0; i < path.size(); i++)
    // {
    //     cout<<path[i].first<<" "<<path[i].second<<endl;
    // }
    // cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
    
    player = Body(xPlay,yPlay,l,r,t,b,0.2,1.0,1,1);
    imposter = Body(xPlay2,yPlay2,l,r,t,b,0.2,0,0,0);
    boomerang1 = Boomer(xboom1,yboom1,l,r,t,b,0.3,0,0,0,1);
    boomerang2 = Boomer(xboom2,yboom2,l,r,t,b,0.3,0,0,0,1);
    boomerang3 = Boomer(xboom3,yboom3,l,r,t,b,0.3,0,0,0,0);
    vaporize1 = Vaporize(xvap1,yvap1,l,r,t,b,0.3,0,0,0,1);
    vaporize2 = Vaporize(xvap2,yvap2,l,r,t,b,0.3,0,0,0,2);
    endd = Gate(16,7,l,r,t,b,0.3,0,0,0,0);
    endd1 = Gate(0,7,l,r,t,b,0.3,0,0,0,0);
    win = Board(4,4,l,r,t,b,1.0,0.0,0.0,1.0,0);
    loss = Board(4,4,l,r,t,b,1.0,0.0,0.0,0.0,1);


    // for (int  i = 0; i < 17; i++)
    // {
    //     // cout<<path[i].first<<" "<<path[i].second<<endl;
    //     for (int j = 0; j < 17; j++)
    //     // {
    //         cout<<bfsmap[7][i][j]<<" ";
        
    //     //     // cout<<"("<<i<<","<<j<<")  ->  ";
    //     //     // for (int k = 0; k < graph[i][j].size(); k++)
    //     //     // {
    //     //     //     cout<<"["<<graph[i][j][k].first<<","<<graph[i][j][k].second<<"] ";
    //     //     // }
            
    //         cout<<endl;
    //     // }
    // }

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers
        if(changePlay==1){
            changePlay=0;
            player = Body(xPlay,yPlay,l,r,t,b,0.2,1.0,1,1);
        }

        if(changePlay2==0){
        
            int a=heavy_driver();
            // int a=3;
            // cout<<a<<endl;
            if(a==1)xPlay2-=1;
            if(a==2)xPlay2+=1;
            if(a==3)yPlay2-=1;
            if(a==4)yPlay2+=1;
            changePlay2=1;
        }

        if(t1.processTick())
        {
            if(changePlay2==1){
                changePlay2=0;
                imposter = Body(xPlay2,yPlay2,l,r,t,b,0.2,0,0,0);
            }

            if(status=="op")
            TOTIME-=1;
        }

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            // if(status=="op")
            draw();
            if(mmm==1)
            msg_TO_HUD();
            // else
            
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
