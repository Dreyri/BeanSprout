#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Signal
#include <boost/test/unit_test.hpp>
#include "signal/signal.h"

using namespace BS;

BOOST_AUTO_TEST_CASE(attach)
{
    Signal<void(int)> sig;

    auto lambda = [](int x)
    {
        BOOST_CHECK(x == 5);
    };

    sig.connect(lambda);

    sig(5);
}

BOOST_AUTO_TEST_CASE(lambda_capture)
{
    Signal<void(int)> sig;
    int i = 5;

    auto lambda = [&](int x)
    {
        ++i;
    };

    sig.connect(lambda);

    sig(0);

    BOOST_CHECK(i == 6);
}

BOOST_AUTO_TEST_CASE(multiple_connect_disconnect)
{
    Signal<void(int*)> sig;
    int i = 0;

    auto increment = [](int* i)
    {
        ++(*i);
    };

    auto slot1 = sig.connect(increment);
    auto slot2 = sig.connect(increment);

    sig(&i);

    BOOST_CHECK(i == 2);

    sig.disconnect(slot1);

    sig(&i);
    BOOST_CHECK(i == 3);
}

BOOST_AUTO_TEST_CASE(locks)
{
    Signal<void()> sig;

    int i = 0;

    auto increment = [&]()
    {
        ++i;
    };

    auto slot = sig.connect(increment);

    slot->lock();
    sig();
    BOOST_CHECK(i == 0);
    slot->unlock();

    sig();
    BOOST_CHECK(i == 1);

    sig.lock();
    sig();
    BOOST_CHECK(i == 1);
    sig.unlock();
}

BOOST_AUTO_TEST_CASE(timeout)
{
    Signal<void()> sig;

    int i = 0;

    auto increment = [&]()
    {
        ++i;
    };

    auto slot = sig.connect(increment);

    sig.setTimeout(1000);

    //if this takes over 1000ms, kill me
    for(int i = 0; i < 10; ++i)
        sig();

    BOOST_CHECK(i == 1);

    //if we set timeout to a new value it should immediately be used
    sig.setTimeout(0);
    sig();

    BOOST_CHECK(i == 2);

    slot->setTimeout(1000);

    for(int i = 0; i < 10; ++i)
        sig();

    BOOST_CHECK(i == 3);

    slot->setTimeout(0);

    sig();

    BOOST_CHECK(i == 4);
}
