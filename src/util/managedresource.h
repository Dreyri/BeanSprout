#pragma once

#include "util/weakresource.h"
#include "util/resource.h"
#include "util/fileloader.h"
#include <boost/filesystem.hpp>
#include <functional>

using namespace boost::filesystem;

namespace BS
{

template<typename T, typename FileLoader = FileLoader<T> >
class ManagedResource
{
private:
    WeakResource<T> mResource;
    std::string mId;
    path mPath;
    bool mIsValid;
public:
    ManagedResource(const std::string& name, const path& path)
        : mResource(), mId(name), mPath(path), mIsValid(false)
    {
        //if path is empty it's most likely a dummy for searching
        //if(!exists(mPath) && !mPath.empty())
        //    std::cout << "W: " << absolute(path) << " does not exist!" << std::endl;
        if(!path.empty())
            if(FileLoader::validate(path))
                mIsValid = true;
    }

    Resource<T> get()
    {
        if(mResource)
            return mResource.lock();
        else if(mIsValid)
        {
            auto res = FileLoader::load(mPath);
            mResource = res;
            return res;
        }

        return Resource<T>(nullptr);
    }

    const std::string& getId() const
    {
        return mId;
    }

    /**
     * checks if the managedresource points to a valid file
     */
    bool validate() const
    {
        return FileLoader::validate(mPath);
    }
};

struct MResourceCompare
{
    template<typename T>
    bool operator()(const ManagedResource<T>& lhs, const ManagedResource<T>& rhs) const
    {
        return lhs.getId() == rhs.getId();
    }
};

struct MResourceHash
{
    template<typename T>
    size_t operator() (const ManagedResource<T>& mr) const
    {
        return std::hash<std::string>()(mr.getId());
    }
};
}
