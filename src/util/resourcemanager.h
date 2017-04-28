#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <map>

#include "graphics/texture2d.h"

namespace BS
{
class ResourceManager
{
private:
    std::map<std::string, Texture2D> mTextures;
public:
    ResourceManager();

    const Texture2D& getTexture(const std::string& name);
};
}

#endif // RESOURCEMANAGER_H
