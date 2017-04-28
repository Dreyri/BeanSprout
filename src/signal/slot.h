#ifndef SLOT_H
#define SLOT_H

#include <functional>
#include <chrono>

namespace BS
{
template<typename T>
class Slot {};

template<typename... Args>
class Slot<void(Args...)>
{
    typedef std::function<void(Args...)> Function;
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::time_point<Clock> TimePoint;

private:
    Function mFunc;
    int mTimeout;
    bool mIsLocked;

    TimePoint mLastCall;

public:
    Slot(const Function& f)
        : mFunc(f), mTimeout(0), mIsLocked(false), mLastCall()
    {}

    void setTimeout(int timeoutms)
    {
        mTimeout = timeoutms;
    }

    const int&  getTimeoutMs() const
    {
        return mTimeout;
    }

    bool isLocked() const
    {
        return mIsLocked;
    }

    void lock()
    {
        mIsLocked = true;
    }

    void unlock()
    {
        mIsLocked = false;
    }

    void operator()(Args... args)
    {
        if(mIsLocked)
            return;

        if(mTimeout != 0)
        {
            auto now = Clock::now();

            //return if our time hasn't come yet
            if((mLastCall + std::chrono::milliseconds(mTimeout)) > now)
            {
                return;
            }

            mLastCall = now;
        }

        mFunc(args...);


    }
};
}

#endif // SLOT_H
