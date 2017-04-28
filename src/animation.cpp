#include "animation.h"

Animation::Animation(SpriteSheet sheet)
{
    mSheet = sheet;
    mIsRunning = false;
}

Animation::~Animation()
{}

bool Animation::define(int id, std::vector<AnimationFrame> frames)
{
    mId = id;
    mFrames = frames;
}

void Animation::update(std::chrono::high_resolution_clock::time_point curTime)
{
    if(!mIsRunning)
        mStart = curTime;

    mCurrent = curTime;
}

void Animation::run()
{
    mIsRunning = true;

    mStart = mCurrent;
}

void Animation::cancel()
{
    mIsRunning = false;

    mStart = mCurrent;

}

bool Animation::isRunning()
{
    return mIsRunning;
}

int Animation::getAnimationLength()
{
    int duration = 0;

    for(int i = 0; i < mFrames.size(); ++i)
    {
        duration += mFrames[i].duration;
    }

    return duration;
}

int Animation::getRemainingDuration()
{
    return getAnimationLength() - getRuntime();
}

int Animation::getRuntime()
{
    int duration = std::chrono::duration_cast<std::chrono::milliseconds>(mCurrent - mStart).count();

    return duration;
}

void Animation::setAnimationTime(int timems)
{
    std::chrono::milliseconds ms(timems);

    mStart = mCurrent - ms;
}

int Animation::getFrameAmount()
{
    return mFrames.size();
}

int Animation::getCurrentFrame()
{
    int runTime = getRuntime() % getAnimationLength();

    int duration = 0;
    
    for(int i = 0; i < mFrames.size(); ++i)
    {
        duration += mFrames[i].duration;

        if(runTime < duration)
            return i;
    }

    //error
    return -1;
}

int Animation::getSprite(int frame)
{
    return mFrames[frame].sprite;
}

int Animation::getCurrentSprite()
{
    return getSprite(getCurrentFrame());
}
