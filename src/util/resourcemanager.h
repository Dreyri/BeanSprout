#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <unordered_set>
#include <boost/filesystem.hpp>

#include "graphics/texture2d.h"
#include "util/weakresource.h"
#include "util/resource.h"
#include "util/managedresource.h"

using namespace boost::filesystem;

namespace BS
{
class ResourceManager
{
    template<typename T>
    using ResourceSet = std::unordered_set<ManagedResource<T>, MResourceHash, MResourceCompare>;
    typedef ResourceSet<Texture2D> TextureSet;
    typedef ResourceSet<ShaderProgram> ShaderProgramSet;
private:
    TextureSet mTextures;
    ShaderProgramSet mShaderPrograms;
public:
    ResourceManager();
    ~ResourceManager();

    Resource<Texture2D> getTexture(const std::string& id);
    bool addTexture(const std::string& id, const path& p);

    Resource<ShaderProgram> getShaderProgram(const std::string& id);
    bool addShaderProgram(const std::string& id, const path& p);

private:
    template<typename T>
    Resource<T> getResource(ResourceSet<T>& set, const std::string& id)
    {
        auto it = set.find(ManagedResource<T>(id, path()));
        if(it == set.end())
        {
            std::cout << "W: could not find \"" << id << "\"!" << std::endl;
            return Resource<T>();
        }
        else
        {
            //we have to remove the managedresource from our set currently because
            //obviously they're immutable
            //it isn't too expensive so meh I guess
            auto resource(*it);
            set.erase(it);
            auto res = resource.get();
            set.insert(resource);
            return res;
        }
    }

    /**
     * add resource to our set, fails if it already exists
     */
    template<typename T>
    bool addResource(ResourceSet<T>& set, const std::string& id, const path& p)
    {
        auto mres = ManagedResource<T>(id, p);
        if(mres.validate())
        {
            auto success = set.insert(mres);
            if(success.second)
            {
                std::cout << "Added " << p << " as \"" << id << "\"" << std::endl;
                return true;
            }
            else
            {
                std::cout << "W: could not add \"" << id << "\" already exists!" << std::endl;
            }
        }

        return false;
    }
};
}

#endif // RESOURCEMANAGER_H
