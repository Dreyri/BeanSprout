#include "util/freeimage_loader.h"

namespace BS
{
Resource<Texture2D> FreeImageLoader::loadTexture(const char* filename, GLenum image_format, GLint internal_format)
{
    //image format
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
    //pointer to the image, once loaded
    FIBITMAP *dib(0);
    //pointer to the image data
    BYTE* bits(0);
    //image width and height
    unsigned int width(0), height(0);

    //check the file signature and deduce its format
    fif = FreeImage_GetFileType(filename, 0);
    //if still unknown, try to guess the file format from the file extension
    if(fif == FIF_UNKNOWN)
        fif = FreeImage_GetFIFFromFilename(filename);
    //if still unkown, return failure
    if(fif == FIF_UNKNOWN)
        return Resource<Texture2D>(nullptr);

    //check that the plugin has reading capabilities and load the file
    if(FreeImage_FIFSupportsReading(fif))
        dib = FreeImage_Load(fif, filename);
    //if the image failed to load, return failure
    if(!dib)
        return Resource<Texture2D>(nullptr);

    //retrieve the image data
    bits = FreeImage_GetBits(dib);
    //get the image width and height
    width = FreeImage_GetWidth(dib);
    height = FreeImage_GetHeight(dib);
    //if this somehow one of these failed (they shouldn't), return failure
    if((bits == 0) || (width == 0) || (height == 0))
        return Resource<Texture2D>(nullptr);


    Texture2D* res = new Texture2D(width, height, internal_format, image_format, bits);

    //Free FreeImage's copy of the data
    FreeImage_Unload(dib);

    //return success
    return Resource<Texture2D>(res);

}
}
