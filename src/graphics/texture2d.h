#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <GLES2/gl2.h>
#include <GL/gl.h>

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
    Texture2D(GLuint width, GLuint height, unsigned char* data);

    void bind() const;
};
}

#endif // TEXTURE2D_H
