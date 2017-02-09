#include "app.h"

void App::setup(){
   
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
        "   color = vec4(gl_FragCoord.x/640.0, gl_FragCoord.y/480.0, 1.0, 1.0);\n"
        "}\n"
    );

   testShader.load(strVertexShader, strFragmentShader);
    
}

void App::draw(){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(testShader.program);
    plane.draw();
}
