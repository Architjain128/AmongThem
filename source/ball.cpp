#include "ball.h"
#include "main.h"


Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        0.3,0.85,0,
        0.7,0.85,0,
        0.7,0.35,0,

        0.7,0.35,0,
        0.3,0.35,0,
        0.3,0.85,0,

        0.7,0.35,0,
        0.3,0.35,0,
        0.4,0.20,0,

        0.7,0.35,0,
        0.5,0.15,0,
        0.4,0.20,0,

        0.7,0.35,0,
        0.5,0.15,0,
        0.6,0.20,0,

        0.4,0.4,0,
        0.6,0.3,0,
        0.6,0.4,0,

        0.4,0.4,0,
        0.4,0.3,0,
        0.6,0.3,0,
    };
    static const GLfloat color_buffer_data[] = {
        0,0,1,
        0,0,1,
        0,0,1,

        0,0,1,
        0,0,1,
        0,0,1,
        
        0,0,1,
        0,0,1,
        0,0,1,
        
        0,0,1,
        0,0,1,
        0,0,1,
        
        0,0,1,
        0,0,1,
        0,0,1,

        168,204,215,
        168,204,215,
        168,204,215,
        
        168,204,215,
        168,204,215,
        168,204,215,

    };

    this->object = create3DObject(GL_TRIANGLES, 7*3, vertex_buffer_data, color_buffer_data, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) ( M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

