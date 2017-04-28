#include "sprite_sheet.h"

SpriteSheet::SpriteSheet()
{
    mFrameWidth = 0;
    mFrameHeight = 0;
    mTexture = NULL;
    mSpriteClips = NULL;
}

SpriteSheet::SpriteSheet(int frameWidth, int frameHeight)
{
    mFrameWidth = frameWidth;
    mFrameHeight = frameHeight;
    mTexture = NULL;
    mSpriteClips = NULL;
}

SpriteSheet::SpriteSheet(const SpriteSheet &copy)
{
    this->mFrameHeight = copy.mFrameHeight;
    this->mFrameWidth = copy.mFrameWidth;

    this->mHeight = copy.mHeight;
    this->mWidth = copy.mWidth;

    this->mTotalFrames = copy.mTotalFrames;
    
    this->mTexture = copy.mTexture;
    this->mSpriteClips = copy.mSpriteClips;
}

SpriteSheet::~SpriteSheet()
{
    if(mTexture != NULL)
        SDL_DestroyTexture(mTexture);
    if(mSpriteClips != NULL)
        delete[] mSpriteClips;
}

bool SpriteSheet::textureLoaded()
{
    if(mTexture == NULL)
        return false;

    return true;
}


bool SpriteSheet::loadFromFile(SDL_Renderer* renderer, const char* file)
{
    if(mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
    }

    if(mSpriteClips != NULL)
    {
        delete[] mSpriteClips;
        mSpriteClips = NULL;
    }

    mMedia = file;

    SDL_Surface* surface = IMG_Load(file);
    mTexture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    if(mTexture == NULL)
    {
        printf("Unable to load image %s! SDL_Error: %s\n", file, SDL_GetError());
        return false;
    }
    int width = 0;
    int height = 0;

    SDL_QueryTexture(mTexture, NULL, NULL, &width, &height);

    mWidth = width;
    mHeight = height;

    int framesWidth = width/mFrameWidth;
    int framesHeight = height/mFrameHeight;

    int totalFrames = framesWidth * framesHeight;
    mTotalFrames = totalFrames;

    mSpriteClips = new SDL_Rect[totalFrames];

    for(int i = 0; i < mTotalFrames; ++i)
    {
        mSpriteClips[i].x = (i%framesWidth) * mFrameWidth;
        mSpriteClips[i].y = (i/framesWidth) * mFrameHeight;
        mSpriteClips[i].w = mFrameWidth;
        mSpriteClips[i].h = mFrameHeight;
        //printf("Clip %i created at %i, %i with %i, %i\n", i, mSpriteClips[i].x, mSpriteClips[i].y, mSpriteClips[i].w, mSpriteClips[i].h);
    }

    printf("Loaded file: %s, width: %i, height: %i, frames: %i\n", mMedia.c_str(), mWidth, mHeight, mTotalFrames);

    return true;
}

void SpriteSheet::render(SDL_Renderer* renderer, int x, int y, SDL_RendererFlip flip, int sprite)
{
    SDL_Rect renderQuad = { x, y, mFrameWidth, mFrameHeight };

    SDL_Rect spriteRect = mSpriteClips[sprite];

    //printf("Rendered sprite sheet\n");
    //printf("Drawing texture %s:%i at %i, %i\n", mMedia.c_str(), sprite, x, y);

    SDL_RenderCopyEx(renderer, mTexture, &spriteRect, &renderQuad, 0, NULL, flip);
}

int SpriteSheet::getSheetWidth()
{
    if(!textureLoaded())
        return -1;

    return mWidth;
}

int SpriteSheet::getSheetHeight()
{
    if(!textureLoaded())
        return -1;

    return mHeight;
}

int SpriteSheet::getFrameWidth()
{
    return mFrameWidth;
}

int SpriteSheet::getFrameHeight()
{
    return mFrameHeight;
}
