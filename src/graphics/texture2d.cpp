#include "graphics/texture2d.h"

namespace BS
{
Texture2D::Texture2D(GLuint width, GLuint height, GLuint internalFormat, GLuint imageFormat, unsigned char* data)
    : mWidth(width), mHeight(height), mInternalFormat(internalFormat), mImageFormat(imageFormat), mWrapS(GL_REPEAT), mWrapT(GL_REPEAT), mFilterMin(GL_LINEAR), mFilterMax(GL_LINEAR)
{
    //generate texture
    glGenTextures(1 , &mId);
    //create texture
    glBindTexture(GL_TEXTURE_2D, mId);
    glTexImage2D(GL_TEXTURE_2D, 0, mInternalFormat, mWidth, mHeight, 0, mImageFormat, GL_UNSIGNED_BYTE, data);
    //set texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mWrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mWrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mFilterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mFilterMax);
    //unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::bind() const
{
    glBindTexture(GL_TEXTURE_2D, mId);
}

GLuint Texture2D::getWidth() const
{
    return mWidth;
}

GLuint Texture2D::getHeight() const
{
    return mHeight;
}
}
