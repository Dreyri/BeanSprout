#ifndef RESOURCE_H
#define RESOURCE_H

#include <algorithm>

namespace BS
{

class RefCounter
{
private:
    int mRefCounter;
    int mWkRefCounter;
public:
    RefCounter()
        : mRefCounter(0), mWkRefCounter(0) {}

    void incrRef() { ++mRefCounter; ++mWkRefCounter; }
    void decrRef() { --mRefCounter; --mWkRefCounter; }

    void incrWkRef() { ++mWkRefCounter; }
    void decrWkRef() { --mWkRefCounter; }

    int getRef() { return mRefCounter; }
    int getWkRef() { return mWkRefCounter; }

    template<typename T>
    friend class Resource;
    template<typename T>
    friend class WeakResource;
};

template <typename T>
class WeakResource;

template<typename T>
class Resource
{
private:
    T* mObj;
    RefCounter* mRefCounter;
public:
    Resource()
        : Resource(nullptr) {}
    Resource(T* obj)
        : mObj(obj), mRefCounter(new RefCounter())
    {
        mRefCounter->incrRef();
    }

    Resource(const Resource<T>& res)
        : mObj(res.mObj), mRefCounter(res.mRefCounter)
    {
        //increase reference
        mRefCounter->incrRef();
    }

    ~Resource()
    {
        //decrease reference and delete obj if 0
        mRefCounter->decrRef();
        if(mRefCounter->getRef() == 0)
        {
            delete mObj;
            //if no others are referencing to this, this is our responsibility now
            if(mRefCounter->getWkRef() == 0)
                delete mRefCounter;
        }
    }

    const Resource<T>& operator=(Resource<T> res)
    {
        //let's hope this automatically increments correctly, will test
        swap(*this, res);
        return *this;
    }

    int getReferences() const { return mRefCounter->getRef(); }
    int getAllReferences() const { return mRefCounter->getWkRef(); }

    const T& operator*() const
    {
        return *mObj;
    }

    T& operator*()
    {
        return *mObj;
    }

    T* operator->() { return mObj; }
    const T* operator->() const { return mObj; }

    operator bool() const
    {
        return mObj != nullptr;
    }

    friend void swap(Resource<T>& r1, Resource<T>& r2)
    {
        std::swap(r1.mObj, r2.mObj);
        std::swap(r1.mRefCounter, r2.mRefCounter);
    }
private:
    Resource(T* obj, RefCounter* refCounter)
        : mObj(obj), mRefCounter(refCounter)
    {
        mRefCounter->incrRef();
    }

    friend class WeakResource<T>;
};
}

#endif // RESOURCE_H
