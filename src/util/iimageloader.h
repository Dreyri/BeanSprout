#pragma once

#include <string>

#include "graphics/texture2d.h"

namespace BS
{
class IImageLoader
{
public:
    virtual ~IImageLoader() = 0;
    virtual std::string getExtension() const = 0;

    virtual std::shared_ptr<Texture2D> loadTexture(const std::string& path) = 0;

};
}
