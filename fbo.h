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
#include <GLFW/glfw3.h>


class Fbo {
    public:
        GLuint fboId;
        GLuint textureId;
        int width, height;
    
        void allocate(int w, int h, GLenum internalFormat);
        void begin();
        void end();
        void draw();



};
