#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>

class Plane {
    public:
        Plane();
        GLuint vao;
        GLuint positionBufferObject;
        void draw();

};
