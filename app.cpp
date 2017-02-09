#include "app.h"

void App::setup(){
    testShader.load("base.vert", "base.frag");    
}

void App::draw(){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(testShader.program);
    plane.draw();
}
