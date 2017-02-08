#include <stdlib.h>
#include <string>
#include <algorithm>
#include <vector>
#include <GLFW/glfw3.h>

class Shader {
    public:
        GLuint loadShader(GLenum eShaderType, const std::string &fileName);
        GLuint createProgram(const std::vector<GLuint> &shaderList); 
        GLuint program;
        void load(const std::string &vShaderFilename, const std::string &fShaderFilename);
};
