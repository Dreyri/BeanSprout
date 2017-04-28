#pragma once

#include <vector>

#include "animation.h"
#include "sprite_sheet.h"

class Character {
private:
    std::vector<Animation> mAnimations;

    SpriteSheet* mSprite;

    int mDirection;

public:
    Character();
    Character(SpriteSheet* sprite);

    void insertAnimation(const Animation& anim);

    void render(SDL_Renderer* renderer, int x, int y);

    int getDirection();
    void setDirection(int direction);

};
