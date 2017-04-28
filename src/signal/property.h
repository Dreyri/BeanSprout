#ifndef _PROPERTY_H_
#define _PROPERTY_H_

#include "signal.h"

namespace BS
{
template<typename T>
class Property
{
    typedef Signal<T> SignalT;
private:
    SignalT mSignal;
    T mValue;

public:
    Property(T t)
        : mSignal(), mValue(t)
    {}

    ~Property() {}

    void set(const T& val)
    {
        mValue = val;
        mSignal(mValue);
    }

    const T& get() const
    {
        return mValue;
    }

    const T& operator()() const
    {
        return get();
    }
};
}

#endif
