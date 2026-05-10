#include <assert.h>

#include "RegistryOfKnights.hpp"

#include "test_registry.hpp"
#include <cstring>

int main() {
    RK::RegistryOfKnights registry;
    add_test_data(registry);

    tools::Queue<RK::Knight> house_search_results;
    registry.getKnightsOfHouse("Pendragon", house_search_results);
    
    assert(house_search_results.getSize() == 4);

    while (!house_search_results.isEmpty()) {
        assert(strcmp(house_search_results.dequeue()->house, "Pendragon") == 0);
    }

    return 0;
}