#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <string.h>
#include <FreeImage.h>
//#include <GL/glew.h>
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include "plane.h"

class Fbo {
    public:
        GLuint fboId;
        GLuint textureId;
        int width, height;
    
        void allocate(int w, int h, GLenum internalFormat);
        void begin();
        void end();
        void draw();
        GLuint getTexture();
  private:
        Plane plane;


};
