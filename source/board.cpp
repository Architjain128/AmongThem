#include "board.h"
#include "main.h"


Board::Board(float x,float y, float l, float r,float t, float b,float z, float cr,float cg,float cb,int fl) {
    float sx = abs(l-r)/17.0;
    float sy = abs(t-b)/17.0;
    x=9.25*(x)/17.0;
    y=7.1*(-y)/17.0;
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    float z2=z+0.1;

    int val = 0;
    
    static const GLfloat vertex1[] = {
        0.0,0.0,z,
        0.0,1.2,z,
        2.0,1.2,z,

        0.0,0.0,z,
        2.0,1.2,z,
        2.0,0.0,z,

        0.7,0.4,z2,
        0.8,0.3,z2,
        1.2,0.9,z2,

        1.3,0.8,z2,
        0.8,0.3,z2,
        1.2,0.9,z2,

        0.7,0.8,z2,
        0.8,0.9,z2,
        1.2,0.3,z2,

        1.3,0.4,z2,
        0.8,0.9,z2,
        1.2,0.3,z2,
    };

    static const GLfloat vertex2[] = {
        0.0,0.0,z,
        0.0,1.2,z,
        2.0,1.2,z,

        0.0,0.0,z,
        2.0,1.2,z,
        2.0,0.0,z,

        0.8,0.8,z2,
        0.7,0.6,z2,
        1.2,0.8,z2,

        1.3,0.6,z2,
        0.7,0.6,z2,
        1.2,0.8,z2,

        0.6,0.4,z2,
        0.7,0.6,z2,
        0.8,0.6,z2,

        0.9,0.4,z2,
        1.0,0.6,z2,
        0.8,0.6,z2,
        
        1.1,0.4,z2,
        1.0,0.6,z2,
        1.2,0.6,z2,
        
        1.4,0.4,z2,
        1.2,0.6,z2,
        1.3,0.6,z2,
    };

    float zza=x;
    float zzb=-y;
    int bzb;
    if(fl==1)bzb = 54;
    else bzb = 72;

    GLfloat vertex_buffer_data[bzb];
    GLfloat color_buffer_data[bzb];

    static const GLfloat color_buffer_data2[] = {
        
        162.0/256.0, 0.0/256.0, 255.0/256.0,
        162.0/256.0, 0.0/256.0, 255.0/256.0,
        162.0/256.0, 0.0/256.0, 255.0/256.0,

        162.0/256.0, 0.0/256.0, 255.0/256.0,
        162.0/256.0, 0.0/256.0, 255.0/256.0,
        162.0/256.0, 0.0/256.0, 255.0/256.0,
        
        255.0/256.0, 251.0/256.0, 0.0,
        255.0/256.0, 251.0/256.0, 0.0,
        255.0/256.0, 251.0/256.0, 0.0,

        255.0/256.0, 251.0/256.0, 0.0,
        255.0/256.0, 251.0/256.0, 0.0,
        255.0/256.0, 251.0/256.0, 0.0,

        255.0/256.0, 251.0/256.0, 0.0,
        255.0/256.0, 251.0/256.0, 0.0,
        255.0/256.0, 251.0/256.0, 0.0,

        255.0/256.0, 251.0/256.0, 0.0,
        255.0/256.0, 251.0/256.0, 0.0,
        255.0/256.0, 251.0/256.0, 0.0,

        255.0/256.0, 251.0/256.0, 0.0,
        255.0/256.0, 251.0/256.0, 0.0,
        255.0/256.0, 251.0/256.0, 0.0,

        255.0/256.0, 251.0/256.0, 0.0,
        255.0/256.0, 251.0/256.0, 0.0,
        255.0/256.0, 251.0/256.0, 0.0,
    };
    static const GLfloat color_buffer_data1[] = {
        
        // 135.0/256.0, 103.0/256.0, 23.0/256.0,
        // 135.0/256.0, 103.0/256.0, 23.0/256.0,
        // 135.0/256.0, 103.0/256.0, 23.0/256.0,

        // 135.0/256.0, 103.0/256.0, 23.0/256.0,
        // 135.0/256.0, 103.0/256.0, 23.0/256.0,
        // 135.0/256.0, 103.0/256.0, 23.0/256.0,       


       162.0/256.0, 0.0/256.0, 255.0/256.0,
        162.0/256.0, 0.0/256.0, 255.0/256.0,
        162.0/256.0, 0.0/256.0, 255.0/256.0,

        162.0/256.0, 0.0/256.0, 255.0/256.0,
        162.0/256.0, 0.0/256.0, 255.0/256.0,
        162.0/256.0, 0.0/256.0, 255.0/256.0,
        1,0,0,
        1,0,0,
        1,0,0,

        1,0,0,
        1,0,0,
        1,0,0,

        1,0,0,
        1,0,0,
        1,0,0,

        1,0,0,
        1,0,0,
        1,0,0,
    };


    if(fl == 1){
        for(int i=0;i<54;i++){
            if(i%3==0)
            vertex_buffer_data[i]= -2.5+sx*(x+16-5.0*vertex1[i]-0.2);

            else if(i%3==1)
            vertex_buffer_data[i]=-2.0+sy*(y+4.0*vertex1[i]);

            else if(i%3==2)
            vertex_buffer_data[i]= vertex1[i];
        }

        for(int i=0;i<54;i++){
            color_buffer_data[i] = color_buffer_data1[i]; 
        }
        val = 18;
    }
    else{
        for(int i=0;i<72;i++){
            if(i%3==0)
            vertex_buffer_data[i]= -2.5+sx*(x+16-5.0*vertex2[i]-0.2);

            else if(i%3==1)
            vertex_buffer_data[i]=-2.0+sy*(y+4.0*vertex2[i]);

            else if(i%3==2)
            vertex_buffer_data[i]= vertex1[i];
        }

        for(int i=0;i<72;i++){
            color_buffer_data[i] = color_buffer_data2[i]; 
        }
        val = 24;
    }

    
    // std::cout<<color_buffer_data[5]<<std::endl;
    this->object = create3DObject(GL_TRIANGLES, val, vertex_buffer_data, color_buffer_data, GL_FILL);
}

void Board::draw(glm::mat4 VP) {
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

void Board::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Board::tick() {
    // this->rotation += speed;
}

