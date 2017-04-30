#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Signal
#include <boost/test/unit_test.hpp>
#include "util/resource.h"
#include "util/weakresource.h"
#include <iostream>

using namespace BS;

class Test {
private:
    std::string mStr;

public:

    Test(const std::string& str)
        : mStr(str)
    {
        std::cout << "Object: \"" << mStr << "\" created" << std::endl;
    }

    bool awesome() { return true; }

    ~Test()
    {
        std::cout << "Object: \"" << mStr << "\" deleted" << std::endl;
    }
};

BOOST_AUTO_TEST_CASE(references)
{
    Resource<Test> hi(new Test("hi"));
    BOOST_CHECK(hi.getReferences() == 1);

    {
        auto hi2 = Resource<Test>(hi);

        BOOST_CHECK(hi.getReferences() == 2);

        Resource<Test> hi3(new Test("hi3"));
        //hope hi3 original data is destroyed
        hi3 = hi2;

        BOOST_CHECK(hi.getReferences() == hi2.getReferences());
        BOOST_CHECK(hi3.getReferences() == 3);
    }

    BOOST_CHECK(hi);
    BOOST_CHECK(hi->awesome());

    Resource<Test> none(nullptr);
    BOOST_CHECK(!none);
}

BOOST_AUTO_TEST_CASE(weakresource)
{
    Resource<Test> hi(new Test("HI"));
    WeakResource<Test> weakHi(hi);

    BOOST_CHECK(hi.getReferences() == 1);
    BOOST_CHECK(weakHi.getReferences() == 1);

    weakHi.lock();

    BOOST_CHECK(hi.getReferences() == 1);
    BOOST_CHECK(weakHi.getReferences() == 1);

    Resource<Test> hi2 = weakHi.lock();

    BOOST_CHECK(hi2.getReferences() == 2);
    BOOST_CHECK(hi.getReferences() == 2);
    BOOST_CHECK(weakHi.getReferences() == 2);

    {
        Resource<Test> hiAgain(new Test("hi again!"));
        weakHi = hiAgain;

        BOOST_CHECK(hiAgain.getReferences() == 1);
        BOOST_CHECK(weakHi.getReferences() == 1);
    }

    BOOST_CHECK(weakHi.getReferences() == 0);
    BOOST_CHECK(!(weakHi.lock()));
}
