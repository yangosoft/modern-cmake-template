#include "components/component2/component2.hpp"
#include "components/component1/component1.hpp"

using namespace components;

void Component2::init()
{
    Component1 c;
    c.init();
    // Do something
}