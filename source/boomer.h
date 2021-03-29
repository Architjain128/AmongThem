#include "main.h"

#ifndef BOOMER_H
#define BOOMER_H


class Boomer {
public:
    Boomer() {}
    Boomer(float x,float y, float l, float r,float t, float b,float z, float cr,float cg,float cb,int fl);
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
