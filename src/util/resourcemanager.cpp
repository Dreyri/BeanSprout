#include "resourcemanager.h"
#include "FreeImage.h"

namespace BS
{
ResourceManager::ResourceManager()
{
#ifdef FREEIMAGE_MAJOR_VERSION
    FreeImage_Initialise();
#endif
}

ResourceManager::~ResourceManager()
{
#ifdef FREEIMAGE_MAJOR_VERSION
    FreeImage_DeInitialise();
#endif
}

Resource<Texture2D> ResourceManager::getTexture(const std::string& id)
{
    return getResource(mTextures, id);
}

bool ResourceManager::addTexture(const std::string& id, const path& p)
{
    return addResource(mTextures, id, p);
}

Resource<ShaderProgram> ResourceManager::getShaderProgram(const std::string& id)
{
    return getResource(mShaderPrograms, id);
}

bool ResourceManager::addShaderProgram(const std::string& id, const path& p)
{
    return addResource(mShaderPrograms, id, p);
}
}
