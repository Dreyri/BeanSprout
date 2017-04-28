#ifndef RESOURCE_H
#define RESOURCE_H

#include <algorithm>

template<typename T>
class Resource
{
private:
    T* mObj;
    int* mRefCount;
public:
    Resource(T* obj)
        : mObj(obj), mRefCount(new int(1))
    {
    }
    Resource(const Resource<T>& res)
        : mObj(res.mObj), mRefCount(res.mRefCount)
    {
        //increase reference
        ++(*mRefCount);
    }

    ~Resource()
    {
        //decrease reference and delete obj if 0
        --(*mRefCount);
        if(*mRefCount == 0)
            delete mObj;
    }

    const Resource<T>& operator=(Resource<T> res)
    {
        //let's hope this automatically increments correctly, will test
        swap(*this, res);
        return *this;
    }

    int getReferences() const { return *mRefCount; }

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

    friend void swap(Resource<T>& r1, Resource<T>& r2)
    {
        std::swap(r1.mObj, r2.mObj);
        std::swap(r1.mRefCount, r2.mRefCount);
    }
};

#endif // RESOURCE_H
