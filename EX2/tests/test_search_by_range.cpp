#include <cassert>

#include "RegistryOfKnights.hpp"

int main() {
    RK::RegistryOfKnights registry;
    registry.insert("Arthur", 10, 5, "Stark");
    registry.insert("Lancelot", 30, 12, "Lannister");
    registry.insert("Percival", 20, 8, "Stark");
    registry.insert("Gawain", 40, 3, "Baratheon");
    registry.insert("Tristan", 50, 7, "Stark");

    // normal range — should find Lancelot and Percival
    tools::Queue<RK::Knight> result;
    registry.getKnightsByBravery(15, 35, result);
    assert(result.getSize() == 2);
    assert(result.dequeue()->braveryScore == 20); // in ascending order
    assert(result.dequeue()->braveryScore == 30);

    // exact boundary — should include endpoints
    tools::Queue<RK::Knight> result2;
    registry.getKnightsByBravery(10, 10, result2);
    assert(result2.getSize() == 1);
    assert(result2.dequeue()->braveryScore == 10);

    // empty range — nothing in this range
    tools::Queue<RK::Knight> result3;
    registry.getKnightsByBravery(100, 200, result3);
    assert(result3.getSize() == 0);

    return 0;
}