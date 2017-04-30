#pragma once

#include <FreeImage.h>
#include "graphics/texture2d.h"
#include "util/resource.h"

namespace BS
{
class FreeImageLoader
{
public:
    static Resource<Texture2D> loadTexture(const char* filename, GLenum image_format, GLint internal_format);
};

}
