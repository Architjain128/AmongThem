#include "main.h"

#ifndef GATE_H
#define GATE_H


class Gate {
public:
    Gate() {}
    Gate(float x,float y, float l, float r,float t, float b,float z, float cr,float cg,float cb,int fl);
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
