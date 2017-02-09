#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include "plane.h"

Plane::Plane(){
    const float vertexPositions [] = {
        1.0, 1.0, 0.0, 1.0,
        1.0, -1.0, 0.0, 1.0, 
        -1.0, 1.0, 0.0, 1.0,

        1.0, -1.0, 0.0, 1.0,
        -1.0, -1.0, 0.0, 1.0,
        -1.0, 1.0,0.0,1.0,
    };


   glGenBuffers(1, &positionBufferObject);
   glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

   glBindBuffer(GL_ARRAY_BUFFER, 0);

   glGenVertexArrays(1, &vao);
   glBindVertexArray(vao);

}

void Plane::draw(){
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,4,GL_FLOAT, GL_FALSE, 0,0);

    glDrawArrays(GL_TRIANGLES, 0,6);
    glDisableVertexAttribArray(0);
}

