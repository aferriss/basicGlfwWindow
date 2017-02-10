#include "app.h"

void App::setup(){
    testShader.load("base.vert", "base.frag");    
    time = 0;
    tex.load("data/test.png");
}

void App::draw(){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(testShader.program);
    testShader.setUniform1f("time", time);
    testShader.setUniformTexture("tex0", tex.getTexture(),0);
    plane.draw();
    time++;
    
}
