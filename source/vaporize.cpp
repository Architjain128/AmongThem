#include "vaporize.h"
#include "main.h"


Vaporize::Vaporize(float x,float y, float l, float r,float t, float b,float z, float cr,float cg,float cb,int fl) {
    float sx = abs(l-r)/17.0;
    float sy = abs(t-b)/17.0;
    x=9.25*(x)/17.0;
    y=7.1*(-y)/17.0;
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    z=0.3;
static const GLfloat vertex[] = {
    0.5,0.1,z,
    0.3,0.2,z,
    0.7,0.2,z,

    0.5,0.3,z,
    0.3,0.2,z,
    0.7,0.2,z,

    0.4,0.9,z,
    0.6,0.9,z,
    0.4,0.3,z,

    0.6,0.3,z,
    0.6,0.9,z,
    0.4,0.3,z,

};


    GLfloat vertex_buffer_data[36];

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
    static const GLfloat color_buffer_data[] = {
        
        255.0/256.0,37.0/256.0,0.0/256.0,
        255.0/256.0,37.0/256.0,0.0/256.0,
        255.0/256.0,37.0/256.0,0.0/256.0,

        255.0/256.0,37.0/256.0,0.0/256.0,
        255.0/256.0,37.0/256.0,0.0/256.0,
        255.0/256.0,37.0/256.0,0.0/256.0,
        
        150.0/256.0,111.0/256.0,51.0/256.0,
        150.0/256.0,111.0/256.0,51.0/256.0,
        150.0/256.0,111.0/256.0,51.0/256.0,

        150.0/256.0,111.0/256.0,51.0/256.0,
        150.0/256.0,111.0/256.0,51.0/256.0,
        150.0/256.0,111.0/256.0,51.0/256.0,

    };
 
    // std::cout<<color_buffer_data[5]<<std::endl;
    this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, color_buffer_data, GL_FILL);
}

void Vaporize::draw(glm::mat4 VP) {
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

void Vaporize::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Vaporize::tick() {
    // this->rotation += speed;
}

