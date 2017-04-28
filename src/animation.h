#pragma once

#include <vector>
#include <chrono>

#include "sprite_sheet.h"

typedef std::chrono::high_resolution_clock::time_point time_point;

class Animation
{
private:
    int mId;

    struct AnimationFrame
    {
        int sprite;
        int duration;
    };
    //first int is the sprite id, second the number of ms to run for before
    //next sprite
    std::vector<AnimationFrame> mFrames;


    SpriteSheet mSheet;

    bool mIsRunning;

    time_point mStart;
    time_point mCurrent;

public:
    Animation(SpriteSheet sheet);
    ~Animation();

    bool define(int id, std::vector<AnimationFrame> frames);

    void update(time_point curTime);

    void run();
    void cancel();

    bool isRunning();

    int getId() { return mId; }

    int getAnimationLength();
    int getRemainingDuration();
    int getRuntime();

    void setAnimationTime(int timems);

    int getFrameAmount();
    int getCurrentFrame();
    int getSprite(int frame);
    int getCurrentSprite();
};
