#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <OpenGL/gl.h>

namespace BS
{
class Texture2D
{
private:
    GLuint mId;
    GLuint mWidth, mHeight;

    GLuint mInternalFormat;
    GLuint mImageFormat;

    GLuint mWrapS;
    GLuint mWrapT;

    GLuint mFilterMin;
    GLuint mFilterMax;
public:
    Texture2D(GLuint width, GLuint height, GLuint internalFormat, GLuint imageFormat, unsigned char* data);

    void bind() const;

    GLuint getWidth() const;
    GLuint getHeight() const;
};
}

#endif // TEXTURE2D_H
