#include "body.h"
#include "main.h"


Body::Body(float x,float y, float l, float r,float t, float b,float z, float cr,float cg,float cb) {
    float sx = abs(l-r)/17.0;
    float sy = abs(t-b)/17.0;
    x=9.25*(x)/17.0;
    y=7.1*(-y)/17.0;
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    
static const GLfloat vertex[] = {
        0.3,0.85,z,
        0.7,0.85,z,
        0.7,0.35,z,

        0.7,0.35,z,
        0.3,0.35,z,
        0.3,0.85,z,

        0.7,0.35,z,
        0.3,0.35,z,
        0.4,0.20,z,

        0.7,0.35,z,
        0.5,0.15,z,
        0.4,0.20,z,

        0.7,0.35,z,
        0.5,0.15,z,
        0.6,0.20,z,

        0.4,0.45,z,
        0.6,0.35,z,
        0.6,0.45,z,

        0.4,0.45,z,
        0.4,0.35,z,
        0.6,0.35,z,

        0.45,0.85,z,
        0.55,0.75,z,
        0.55,0.85,z,

        0.45,0.85,z,
        0.45,0.75,z,
        0.55,0.75,z,

        0.25,0.35,z,
        0.3,0.75,z,
        0.3,0.35,z,

        0.25,0.35,z,
        0.25,0.75,z,
        0.3,0.75,z,
    };

    GLfloat vertex_buffer_data[99];

    float zza=x;
    float zzb=-y;
    for(int i=0;i<99;i++){
        if(i%3==0)
        vertex_buffer_data[i]= -2.5+sx*(x+16-1.5*vertex[i]-0.2);

        else if(i%3==1)
        vertex_buffer_data[i]=-2.0+sy*(y+vertex[i]);

        else if(i%3==2)
        vertex_buffer_data[i]= vertex[i];
    }

    static const GLfloat color_buffer_data[] = {
        
        cr,cg,cb,
        cr,cg,cb,
        cr,cg,cb,

        cr,cg,cb,
        cr,cg,cb,
        cr,cg,cb,

        cr,cg,cb,
        cr,cg,cb,
        cr,cg,cb,

        cr,cg,cb,
        cr,cg,cb,
        cr,cg,cb,

        cr,cg,cb,
        cr,cg,cb,
        cr,cg,cb,

        168.0/256.0,204.0/256.0,215.0/256.0,
        168.0/256.0,204.0/256.0,215.0/256.0,
        168.0/256.0,204.0/256.0,215.0/256.0,
        168.0/256.0,204.0/256.0,215.0/256.0,
        168.0/256.0,204.0/256.0,215.0/256.0,
        168.0/256.0,204.0/256.0,215.0/256.0,

        
        244.0/256.0, 245.0/256.0, 203.0/256.0, 
        244.0/256.0, 245.0/256.0, 203.0/256.0, 
        244.0/256.0, 245.0/256.0, 203.0/256.0, 

        244.0/256.0, 245.0/256.0, 203.0/256.0, 
        244.0/256.0, 245.0/256.0, 203.0/256.0, 
        244.0/256.0, 245.0/256.0, 203.0/256.0, 

        0,0,0.6,
        0,0,0.6,
        0,0,0.6,

        0,0,0.6,
        0,0,0.6,
        0,0,0.6,

    };
    // std::cout<<color_buffer_data[5]<<std::endl;
    this->object = create3DObject(GL_TRIANGLES, 11*3, vertex_buffer_data, color_buffer_data, GL_FILL);
}

void Body::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (M_PI), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Body::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Body::tick() {
    // this->rotation += speed;
}

