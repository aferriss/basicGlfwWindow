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

class Texture {
    public:
        GLuint textureId;
        int width, height;
        void initFreeImage(bool init = false);
        void load(const std::string fileName);
        void draw();
        void bind();
        GLuint getTexture();    
};
