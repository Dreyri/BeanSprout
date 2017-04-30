#include "util/fileloader.h"
#include "graphics/texture2d.h"
#include "freeimage_loader.h"
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

namespace BS
{

template<>
Resource<Texture2D> FileLoader<Texture2D>::loadImpl(const path& p)
{
    std::cout << "Found extension: " << p.extension() << std::endl;

    return FreeImageLoader::loadTexture(absolute(p).c_str(), GL_RGB, GL_RGB);
}

template<>
Resource<ShaderProgram> FileLoader<ShaderProgram>::loadImpl(const path& p)
{
    path vsP = p;
    path fsP = p;
    vsP += ".vs";
    fsP += ".fs";

    boost::filesystem::ifstream f {vsP};
    const auto fileSz = file_size(vsP);

    std::string resultVS(fileSz, ' ');
    f.read(&resultVS[0], fileSz);
    f.close();

    boost::filesystem::ifstream f1 {fsP};
    const auto sz = file_size(fsP);

    std::string resultFS(sz, ' ');
    f1.read(&resultFS[0], sz);
    f1.close();

    return Resource<ShaderProgram>(new ShaderProgram(resultVS, resultFS));
}

template<>
bool FileLoader<Texture2D>::validate(const path& p)
{
    return validateFile(p);
}

template<>
bool FileLoader<ShaderProgram>::validate(const path& p)
{
    path vsP = p;
    path fsP = p;

    vsP += ".vs";
    fsP += ".fs";

    if(validateFile(vsP))
    {
        if(validateFile(fsP))
        {
            return true;
        }

        std::cout << "E: fragment shader: " << absolute(fsP) << " does not exist!" << std::endl;

    }

    std::cout << "E: vertex shader: " << absolute(vsP) << " does not exist!" << std::endl;
    return false;
}

}
