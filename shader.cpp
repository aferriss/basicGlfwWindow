#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include "shader.h"

GLuint Shader::loadShader(GLenum eShaderType, const std::string &fileName){
    GLuint shader = glCreateShader(eShaderType);
    const char *strFileData = fileName.c_str();
    glShaderSource(shader, 1, &strFileData, NULL);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE){
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

        const char * strShaderType = NULL;
        switch(eShaderType){
            case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
            case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
        }

        fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
        delete[] strInfoLog;

    }

    return shader;
}

GLuint Shader::createProgram(const std::vector<GLuint> &shaderList){
    GLuint program = glCreateProgram();

    for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++){
        glAttachShader(program, shaderList[iLoop]);
    }
    glLinkProgram(program);
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if(status == GL_FALSE){
        GLint infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
        
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
    }

    for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++){
        glDetachShader(program, shaderList[iLoop]);
    }
    return program;
}

void Shader::load(const std::string &vShaderFilename, const std::string &fShaderFilename){
 //cout << "TESTTTTT" <<endl;
    std::vector<GLuint> shaders;
    shaders.push_back(loadShader(GL_VERTEX_SHADER, vShaderFilename));
    shaders.push_back(loadShader(GL_FRAGMENT_SHADER, fShaderFilename));

    program = createProgram(shaders);
    std::for_each(shaders.begin(), shaders.end(), glDeleteShader);
}
