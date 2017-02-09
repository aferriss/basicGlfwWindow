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
#include "shader.h"

#define GLOBAL_FILE_DIR "../data"
#define LOCAL_FILE_DIR "data/"

GLuint Shader::loadShader(GLenum eShaderType, const std::string &fileName){
    std::string strFilename = FindFileOrThrow(fileName);
    std::ifstream shaderFile(strFilename.c_str());
    std::stringstream shaderData;
    shaderData << shaderFile.rdbuf();
    shaderFile.close();
    
    GLuint shader = glCreateShader(eShaderType);
    std::string shaderString = shaderData.str();
    const char *strFileData = shaderString.c_str();
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
    std::vector<GLuint> shaders;
    shaders.push_back(loadShader(GL_VERTEX_SHADER, vShaderFilename));
    shaders.push_back(loadShader(GL_FRAGMENT_SHADER, fShaderFilename));

    program = createProgram(shaders);
    std::for_each(shaders.begin(), shaders.end(), glDeleteShader);
}

std::string Shader::FindFileOrThrow(const std::string &strBasename){
    std::string strFilename = LOCAL_FILE_DIR + strBasename;
    std::ifstream testFile(strFilename.c_str());
    if(testFile.is_open()){
        return strFilename;
    }
    strFilename = GLOBAL_FILE_DIR + strBasename;
    testFile.open(strFilename.c_str());
    if(testFile.is_open()){
        return strFilename;
    }
    throw std::runtime_error("Could not find the file " + strBasename);

}
