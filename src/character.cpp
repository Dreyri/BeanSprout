#include "character.h"

Character::Character()
{
    this->mSprite = NULL;
    this->mSprite = 0;
}

Character::Character(SpriteSheet* sprite)
{
    this->mSprite = sprite;
    this->mDirection = 0;
}

void Character::insertAnimation(const Animation& anim)
{
    mAnimations.push_back(anim);
}

void Character::render(SDL_Renderer* renderer, int x, int y)
{
    int direction = getDirection();
    if(direction >= 315)
        mSprite->render(renderer, x, y, SDL_FLIP_HORIZONTAL, 2);
    else if(direction >= 270)
        mSprite->render(renderer, x, y, SDL_FLIP_HORIZONTAL, 1);
    else if(direction >= 225)
        mSprite->render(renderer, x, y, SDL_FLIP_HORIZONTAL, 0);
    else if(direction >= 180)
        mSprite->render(renderer, x, y, SDL_FLIP_NONE, 3);
    else if(direction >= 135)
        mSprite->render(renderer, x, y, SDL_FLIP_NONE, 0);
    else if(direction >= 90)
        mSprite->render(renderer, x, y, SDL_FLIP_NONE, 1);
    else if(direction >= 45)
        mSprite->render(renderer, x, y, SDL_FLIP_NONE, 2);
    else if(direction >= 0)
        mSprite->render(renderer, x, y, SDL_FLIP_NONE, 4);
    

}

int Character::getDirection()
{
    return mDirection;
}

void Character::setDirection(int direction)
{
    this->mDirection = direction;
}
