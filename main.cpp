#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

static void error_callback(int error, const char* description){
    fprintf(stderr, "Error:%s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods){
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}



void setup(){


}

void draw(){

}


int main(void){
    GLFWwindow* window;
    
    glfwSetErrorCallback(error_callback);

    if(!glfwInit()){
        return -1;
    }

    window = glfwCreateWindow(640, 480, "YOLO", NULL, NULL);

    if(!window){
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    
    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}


