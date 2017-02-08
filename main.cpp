#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>
#include "shader.h"
#include <iostream>

static void error_callback(int error, const char* description){
    fprintf(stderr, "Error:%s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods){
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

Shader testShader;
GLuint positionBufferObject;
GLuint vao;

const float vertexPositions[] = {
    0.75f, 0.75f, 0.0f, 1.0f,
    0.75f, -0.75f, 0.0f, 1.0f,
    -0.75f, -0.75f, 0.0f, 1.0f,
};

const std::string strVertexShader(
	"#version 330\n"
	"layout(location = 0) in vec4 position;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = position;\n"
	"}\n"
);

const std::string strFragmentShader(
    "#version 330\n"
    "out vec4 color;\n"
	"void main()\n"
	"{\n"
	"   color = vec4(1.0, 1.0, 1.0, 1.0);\n"
	"}\n"
);


void setup(){
   testShader.load(strVertexShader, strFragmentShader);
    
   glGenBuffers(1, &positionBufferObject);

   glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

   glBindBuffer(GL_ARRAY_BUFFER, 0);

   glGenVertexArrays(1, &vao);
   glBindVertexArray(vao);
}

void draw(){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(testShader.program);

    glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,4,GL_FLOAT, GL_FALSE, 0,0);

    glDrawArrays(GL_TRIANGLES, 0,3);
    glDisableVertexAttribArray(0);
    glUseProgram(0);


}


int main(void){
    GLFWwindow* window;
    
    glfwSetErrorCallback(error_callback);

    if(!glfwInit()){
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(640, 480, "YOLO", NULL, NULL);

    if(!window){
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    
    setup();
    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);
        draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}


