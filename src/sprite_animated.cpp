#include "sprite_animated.h"

SpriteAnimated::SpriteAnimated(SpriteSheet sheet)
{
    mActiveAnimation = NULL;
}

SpriteAnimated::~SpriteAnimated()
{

}

bool SpriteAnimated::runAnimation(int id)
{
    for(int i = 0; i < mAnimations.size(); ++i)
    {
        if(mAnimations[i].getId() == id)
        {
            mActiveAnimation = &mAnimations[i];
            mActiveAnimation->run();

            return true;
        }
    }
    return false;
}
