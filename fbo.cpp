#include "fbo.h"

void Fbo::allocate(int width, int height, GLenum internalFormat){
    glGenFramebuffers(1, &fboId);
    glBindFramebuffer(GL_FRAMEBUFFER, fboId);

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Fbo::begin(){
    glBindFramebuffer(GL_FRAMEBUFFER, fboId);
}

void Fbo::end(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Fbo::draw(){
    glBindFramebuffer(GL_FRAMEBUFFER, fboId);
    plane.draw();
}


GLuint Fbo::getTexture(){
    return textureId;
}
