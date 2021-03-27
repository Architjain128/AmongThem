#include "main.h"

#ifndef BODY_H
#define BODY_H


class Body {
public:
    Body() {}
    Body(float x,float y,float left, float right,float up,float down,float z, float a,float b, float c);
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
