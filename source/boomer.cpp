#include "boomer.h"
#include "main.h"


Boomer::Boomer(float x,float y, float l, float r,float t, float b,float z, float cr,float cg,float cb,int fl) {
    float sx = abs(l-r)/17.0;
    float sy = abs(t-b)/17.0;
    x=9.25*(x)/17.0;
    y=7.1*(-y)/17.0;
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    z=0.3;
static const GLfloat vertex[] = {
    0.1,0.1,z,
    0.9,0.1,z,
    0.7,0.9,z,

    0.1,0.1,z,
    0.3,0.9,z,
    0.7,0.9,z,

    0.15,0.11,z,
    0.85,0.11,z,
    0.65,0.3,z,

    0.15,0.11,z,
    0.35,0.3,z,
    0.65,0.3,z,

};
// static const GLfloat vertex[] = {
//         0.7,0.9,z,
//         0.5,0.6,z,
//         0.2,0.6,z,

//         0.2,0.6,z,
//         0.5,0.6,z,
//         0.5,0.4,z,

//         0.2,0.6,z,
//         0.5,0.4,z,
//         0.2,0.4,z,

//         0.2,0.4,z,
//         0.5,0.4,z,
//         0.7,0.1,z,

//     };

    GLfloat vertex_buffer_data[36];
    GLfloat color_buffer_data[36];

    float zza=x;
    float zzb=-y;
    for(int i=0;i<36;i++){
        if(i%3==0)
        vertex_buffer_data[i]= -2.5+sx*(x+16-vertex[i]-0.5);

        else if(i%3==1)
        vertex_buffer_data[i]= -2.0+sy*(y+vertex[i]);

        else if(i%3==2)
        vertex_buffer_data[i]= 0.3;
    }
    static const GLfloat color_buffer_data1[] = {
        
        163.0/256.0,163.0/256.0,163.0/256.0,
        163.0/256.0,163.0/256.0,163.0/256.0,
        163.0/256.0,163.0/256.0,163.0/256.0,

        163.0/256.0,163.0/256.0,163.0/256.0,
        163.0/256.0,163.0/256.0,163.0/256.0,
        163.0/256.0,163.0/256.0,163.0/256.0,

        22.0/256.0,193.0/256.0,245.0/256.0,
        22.0/256.0,193.0/256.0,245.0/256.0,
        22.0/256.0,193.0/256.0,245.0/256.0,

        22.0/256.0,193.0/256.0,245.0/256.0,
        22.0/256.0,193.0/256.0,245.0/256.0,
        22.0/256.0,193.0/256.0,245.0/256.0,

    };
    static const GLfloat color_buffer_data2[] = {
        
        163.0/256.0,163.0/256.0,163.0/256.0,
        163.0/256.0,163.0/256.0,163.0/256.0,
        163.0/256.0,163.0/256.0,163.0/256.0,

        163.0/256.0,163.0/256.0,163.0/256.0,
        163.0/256.0,163.0/256.0,163.0/256.0,
        163.0/256.0,163.0/256.0,163.0/256.0,

        255.0/256.0,102.0/256.0,0.0/256.0,
        255.0/256.0,102.0/256.0,0.0/256.0,
        255.0/256.0,102.0/256.0,0.0/256.0,

        255.0/256.0,102.0/256.0,0.0/256.0,
        255.0/256.0,102.0/256.0,0.0/256.0,
        255.0/256.0,102.0/256.0,0.0/256.0,
    };
    for(int i=0;i<36;i++){
        if(fl==1)
        color_buffer_data[i]= color_buffer_data1[i];
        else
        color_buffer_data[i]= color_buffer_data2[i];
    }
    // std::cout<<color_buffer_data[5]<<std::endl;
    this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, color_buffer_data, GL_FILL);
}

void Boomer::draw(glm::mat4 VP) {
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

void Boomer::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Boomer::tick() {
    // this->rotation += speed;
}

