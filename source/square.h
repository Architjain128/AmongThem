#include "main.h"

#ifndef SQUARE_H
#define SQUARE_H


class Square {
public:
    Square() {}
    Square(float left, float right,float up,float down,float z,float a,float b,float c);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // SQUARE_H
