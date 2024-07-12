#include "components/component1/component1.hpp"
#include "components/component2/component2.hpp"

using namespace components;

int main(int /*argc*/, char ** /*argv*/)
{
    Component2 c;
    c.init();
    // Do something
    return 0;
}
