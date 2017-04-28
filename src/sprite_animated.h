#pragma once

#include <vector>
#include <chrono>

#include "sprite_sheet.h"
#include "animation.h"


class SpriteAnimated
{
private:
    std::vector<Animation> mAnimations;

    Animation* mActiveAnimation;
public:
    SpriteAnimated(SpriteSheet sheet);
    ~SpriteAnimated();

    bool runAnimation(int id);

    void render(std::chrono::high_resolution_clock::time_point delta);
};
