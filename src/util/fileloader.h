#ifndef FILELOADER_H
#define FILELOADER_H

#include <boost/filesystem.hpp>
#include <iostream>
#include "util/resource.h"
#include "graphics/shaderprogram.h"

using namespace boost::filesystem;

namespace BS
{

template<typename T>
class FileLoader
{
private:

public:
    static Resource<T> load(const path& p)
    {
        if(validate(p))
            return loadImpl(p);

        return Resource<T>(nullptr);
    }

    static bool validate(const path& p);


    static bool validateFile(const path& p)
    {
        if(exists(p))
        {
            if(is_regular_file(p))
            {
                return true;
            }

        }
        return false;

    }

    static Resource<T> loadImpl(const path& p);
};

}
#endif // FILELOADER_H
