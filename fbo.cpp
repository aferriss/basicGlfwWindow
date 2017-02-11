#include "fbo.h"

void Fbo::allocate(int width, int height, GLenum internalFormat){
    glGenFramebuffers(1, &fboId);
    glBindFrameBuffer(GL_FRAMEBUFFER, fboId);

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFrameBufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT_0, GL_TEXTURE_2D, textureId, 0);
    glBindFrameBuffer(GL_FRAMEBUFFER, 0);
}

void Fbo::begin(){
    glBindFrameBuffer(GL_FRAMEBUFFER, fboId);
}

void Fbo::end(){
    glBindFrameBuffer(GL_FRAMEBUFFER, 0);
}

void Fbo::draw(){

}
