#include "texture.h"

void Texture::initFreeImage(bool init){
    static bool * bFreeImageInited = new bool(false);
    if(!*bFreeImageInited && !init){
        FreeImage_Initialise();
        *bFreeImageInited = true;
    }
    if(*bFreeImageInited && init){
        FreeImage_DeInitialise();
        *bFreeImageInited = false;
    }
}

void Texture::load(const std::string fileName){
    initFreeImage();
    const char* fn = fileName.c_str();
    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(fn, 0);
    if(format == -1){
        exit(-1);
    }
    if(format == FIF_UNKNOWN){
        format = FreeImage_GetFIFFromFilename(fn);
        if(!FreeImage_FIFSupportsReading(format) ){
            exit(-1);
        }
    }
    FIBITMAP* bitmap = FreeImage_Load(format, fn);
    int bpp = FreeImage_GetBPP(bitmap);
    FIBITMAP* bitmap32;
    if(bpp == 32){
        bitmap32 = bitmap;
    } else {
        bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
    }
    width = FreeImage_GetWidth(bitmap32);
    height = FreeImage_GetHeight(bitmap32);
    
    GLubyte* textureData = FreeImage_GetBits(bitmap32);
    GLuint tempTextureID;
    glGenTextures(1, &tempTextureID);
    glBindTexture(GL_TEXTURE_2D, tempTextureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, textureData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

GLenum glError = glGetError();
    if(glError)
    {
        std::cout << "There was an error loading the texture: "<< fileName << std::endl;
 
        switch (glError)
        {
            case GL_INVALID_ENUM:
                std::cout << "Invalid enum." << std::endl;
                break;
 
            case GL_INVALID_VALUE:
                std::cout << "Invalid value." << std::endl;
                break;
 
            case GL_INVALID_OPERATION:
                std::cout << "Invalid operation." << std::endl;
 
            default:
                std::cout << "Unrecognised GLenum." << std::endl;
                break;
        }
 
        std::cout << "See https://www.opengl.org/sdk/docs/man/html/glTexImage2D.xhtml for further details." << std::endl;
    }


    FreeImage_Unload(bitmap32);
    if(bpp != 32){
        FreeImage_Unload(bitmap);
    }
    textureId = tempTextureID;
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::draw(){

}

void Texture::bind(){
   
}

GLuint Texture::getTexture(){
    return textureId;
}


