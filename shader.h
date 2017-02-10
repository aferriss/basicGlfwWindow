#include <stdlib.h>
#include <string>
#include <algorithm>
#include <vector>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <string.h>

class Shader {
    public:
        GLuint loadShader(GLenum eShaderType, const std::string &fileName);
        GLuint createProgram(const std::vector<GLuint> &shaderList); 
        GLuint program;
        void load(const std::string &vShaderFilename, const std::string &fShaderFilename);
        std::string FindFileOrThrow(const std::string &strBasename);
//        void setTexture(
        void setUniformsCache(GLuint &prog);
        GLint getUniformLocation(const std::string &name) const;
        void setUniformTexture(const std::string &name, const GLuint &texId, int slot) const;
        void setUniform1i(const std::string &name, int v1) const;
        void setUniform1f(const std::string &name, float v1) const;
    private:
        std::unordered_map<std::string, GLint> uniformsCache;
};
