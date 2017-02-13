#include "app.h"

void App::setup(){
    testShader.load("base.vert", "base.frag");    
    shader2.load("base.vert", "shader2.frag");
    time = 0;
    tex.load("data/test.png");
    fbo.allocate(640,480,GL_RGB);
}

void App::draw(){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    fbo.begin();
    glUseProgram(shader2.program);
    shader2.setUniformTexture("tex0", tex.getTexture(), 0);
    plane.draw();
    fbo.end();

    glUseProgram(testShader.program);
    testShader.setUniform1f("time", time);
    testShader.setUniformTexture("tex0", fbo.getTexture(),0);
    plane.draw();
    
    time++;
    
}
