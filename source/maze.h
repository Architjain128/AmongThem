#include "main.h"

#ifndef MAZE_H
#define MAZE_H


class Maze {
public:
    Maze() {}
    Maze(float x, float y,float s,GLfloat Mazver[],int a,float l,float r,float t,float b);
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
