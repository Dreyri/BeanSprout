#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Signal
#include <boost/test/unit_test.hpp>
#include "util/resourcemanager.h"
#include "application.h"
using namespace BS;

BOOST_AUTO_TEST_CASE(texture)
{
    Application w;
    Resource<Texture2D> mimikyu = FileLoader<Texture2D>::load("img/mimikyu.png");

    BOOST_CHECK(mimikyu);
}

BOOST_AUTO_TEST_CASE(loadnothing)
{
    //need a context to load shaders
    Application w;
    ResourceManager manager = ResourceManager();

    manager.addTexture("nothing", "loljk");

    auto noTex = manager.getTexture("nothing");

    BOOST_CHECK(!noTex);

    manager.addShaderProgram("noshade", "none");
    auto noShade = manager.getShaderProgram("nothing");

    BOOST_CHECK(!noShade);
}

BOOST_AUTO_TEST_CASE(loadmimikyu)
{
    Application w;
    ResourceManager manager = ResourceManager();

    manager.addTexture("mimikyu", "img/mimikyu.png");

    auto tex = manager.getTexture("mimikyu");
    BOOST_CHECK(tex);
}

BOOST_AUTO_TEST_CASE(loadbasicshader)
{
    Application w;
    ResourceManager manager = ResourceManager();

    manager.addShaderProgram("basic", "shaders/basic");

    auto shade = manager.getShaderProgram("basic");

    BOOST_CHECK(shade);
}
