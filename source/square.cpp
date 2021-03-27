#include "square.h"
#include "main.h"


Square::Square(float left, float right,float up, float down,float z, float a,float b,float c) {
    this->position = glm::vec3(left, up, 0);
    this->rotation = 0;
    speed = 0;
    
    static const GLfloat vertex_buffer_data[] = {
        left,down,z,
        right,down,z,
        right,up,z,
        right,up,z,
        left,down,z,
        left,up,z,
    };
    static const GLfloat color_buffer_data[] = {
        a,b,c,
        a,b,c,
        a,b,c,
        a,b,c,
        a,b,c,
        a,b,c,
    };


    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color_buffer_data, GL_FILL);
}

void Square::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Square::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Square::tick() {
    this->rotation +=1;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

