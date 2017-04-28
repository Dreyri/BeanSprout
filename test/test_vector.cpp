#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Signal
#include <boost/test/unit_test.hpp>
#include "math/vector2.h"

using namespace BS;

BOOST_AUTO_TEST_CASE( translate )
{
    Vector2i test1 = Vector2i(5,5);

    Vector2i translate = Vector2i(1,1);

    test1.translate(translate);

    BOOST_CHECK(test1 == Vector2i(6,6));
}

BOOST_AUTO_TEST_CASE( assign )
{
    Vector2i test = Vector2i(5,5);
    test[0] = 0;
    test[1] = 0;

    BOOST_CHECK(test.getX() == 0 && test.getY() == 0);

    test = Vector2i(2,2);

    BOOST_CHECK(test.getX() == 2 && test.getY() == 2);
}

BOOST_AUTO_TEST_CASE(multiplication)
{
    Vector2i test = Vector2i(1,1);
    Vector2i test1 = test * 3;

    BOOST_CHECK(test1.getX() == 3 && test1.getY() == 3);
    BOOST_CHECK(test.getX() == 1 && test.getY() == 1);
}
