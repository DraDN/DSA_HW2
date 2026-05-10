#include <assert.h>

#include "RegistryOfKnights.hpp"

#include "test_registry.hpp"

int main() {
    RK::RegistryOfKnights registry;
    add_test_data(registry);

    assert(registry.getHeight() == 4);
    tools::Queue<RK::Knight> leafs;
    registry.getLeafs(leafs);
    assert(leafs.getSize() == 4);
    assert(registry.isBalanced() == true);

    return 0;
}