//#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>
#include "shader.h"
#include "plane.h"
#include "texture.h"
#include "fbo.h"
#include <iostream>


class App {
    public:
        void setup();
        void draw();
        
        Plane plane;
        Shader testShader, shader2;
        Texture tex;
        Fbo fbo;
        float time;
};
