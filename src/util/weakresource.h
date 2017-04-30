#ifndef WEAKRESOURCE_H
#define WEAKRESOURCE_H

#include "util/resource.h"

namespace BS
{
template<typename T>
class WeakResource
{
private:
    //Resource<T>* mResource;
    T* mObj;
    RefCounter* mRefCounter;
public:
    WeakResource()
        : mObj(nullptr), mRefCounter(new RefCounter())
    {
        mRefCounter->incrWkRef();
    }

    WeakResource(const Resource<T>& res)
        : mObj(res.mObj), mRefCounter(res.mRefCounter)
    {
        mRefCounter->incrWkRef();
    }

    WeakResource<T>& operator=(WeakResource<T> wr)
    {
        swap(*this, wr);
        return *this;
    }

    WeakResource<T>& operator=(Resource<T> r)
    {
        swap(*this, r);
        return *this;
    }

    ~WeakResource()
    {
        mRefCounter->decrWkRef();
        //we hold shared responsibility over the refcounter
        if(mRefCounter->getWkRef() == 0)
            delete mRefCounter;
    }

    int getReferences() const
    {
        /*
        if(mResource)
            return mResource->getReferences();
        */
        return mRefCounter->getRef();
    }

    int getAllReferences() const
    {
        return mRefCounter->getWkRef();
    }

    Resource<T> lock() const
    {
        if(mRefCounter->getRef() > 0)
        {
            return Resource<T>(mObj, mRefCounter);
        }

        return Resource<T>(nullptr);
    }

    operator bool()
    {
        return mRefCounter->getRef() > 0;
    }

    friend void swap(WeakResource<T>& lhs, WeakResource<T>& rhs)
    {
        std::swap(lhs.mObj, rhs.mObj);
        std::swap(lhs.mRefCounter, rhs.mRefCounter);
    }

    friend void swap(WeakResource<T>& lhs, Resource<T>& rhs)
    {
        //convert differences between wkres and res
        lhs.mRefCounter->incrRef(); lhs.mRefCounter->decrWkRef();
        rhs.mRefCounter->decrRef(); rhs.mRefCounter->incrWkRef();

        std::swap(lhs.mObj, rhs.mObj);
        std::swap(lhs.mRefCounter, rhs.mRefCounter);
    }
};
}

#endif // WEAKRESOURCE_H
