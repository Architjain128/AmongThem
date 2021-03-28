#include "maze.h"
#include "main.h"


Maze::Maze(float x, float y,float s,GLfloat Mazever[],int a,float l,float r,float t,float b) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0;
    int ss = a;
    float sx = abs(r-l)/17.0;
    float sy = abs(t-b)/17.0;

    GLfloat vertex_buffer_data[ss*3];
    for(int i=0;i<3*ss;i++){
        if(i%3==0)
        vertex_buffer_data[i]=-l-r+ sx*Mazever[i];

        else if(i%3==1)
        vertex_buffer_data[i]=b+sy*Mazever[i]+t;

        else if(i%3==2)
        vertex_buffer_data[i]= 0;
    }
    
    this->object = create3DObject(GL_TRIANGLES, ss, vertex_buffer_data, COLOR_GREEN, GL_FILL);
}

void Maze::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation*M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Maze::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Maze::tick() {
    this->rotation +=1;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

