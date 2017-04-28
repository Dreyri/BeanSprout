#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class SpriteSheet
{
private:
    int mFrameWidth;
    int mFrameHeight;

    int mWidth;
    int mHeight;

    int mTotalFrames;

    std::string mMedia;

    SDL_Texture* mTexture;
    SDL_Rect* mSpriteClips;

public:
    SpriteSheet();
    SpriteSheet(int frameWidth, int frameHeight);
    SpriteSheet(const SpriteSheet &copy);

    ~SpriteSheet();

    bool loadFromFile(SDL_Renderer* renderer, const char* file);

    void render(SDL_Renderer* renderer, int x, int y, SDL_RendererFlip flip, int sprite);

    bool textureLoaded();

    int getSheetWidth();
    int getSheetHeight();

    int getFrameWidth();
    int getFrameHeight();
};
