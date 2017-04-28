#ifndef _SIGNAL_H_
#define _SIGNAL_H_

#include <vector>
#include <functional>
#include <chrono>
#include "slot.h"

namespace BS
{
template<typename T>
class Signal {};

template<typename... Args>
class Signal<void(Args...)>
{
    typedef std::function<void(Args...)> CallbackFunc;
    typedef Slot<void(Args...)> ConnectionType;
    typedef std::vector<ConnectionType*> ConnectionList;

    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::time_point<Clock> TimePoint;
private:
    ConnectionList mCallbacks;
    bool mIsLocked;
    int mTimeoutMs;

    TimePoint mLastCall;

public:
    Signal(bool locked = false, int timeout = 0)
        : mIsLocked(locked), mTimeoutMs(timeout), mLastCall()
    {}

    ~Signal()
    {
        disconnectAll();
    }

    void setTimeout(int ms)
    {
        mTimeoutMs = ms;
    }

    int getTimeoutMs() const
    {
        return mTimeoutMs;
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

    ConnectionType* connect(const CallbackFunc& cb)
    {
        ConnectionType* connection = new ConnectionType(cb);
        mCallbacks.push_back(connection);

        return connection;
    }

    void disconnect(ConnectionType* cb)
    {
        mCallbacks.erase(std::remove(mCallbacks.begin(), mCallbacks.end(), cb), mCallbacks.end());
        delete cb;
    }

    void disconnectAll()
    {
        for(auto cb : mCallbacks)
        {
            disconnect(cb);
        }
    }

    void operator()(Args... args)
    {
        if(mIsLocked)
            return;

        if(mTimeoutMs != 0)
        {
            auto now = Clock::now();
            if((mLastCall + std::chrono::milliseconds(mTimeoutMs)) > now)
                return;

            mLastCall = now;
        }

        for(auto cb : mCallbacks)
        {
            (*(cb))(args...);
        }
    }
};
}

#endif
