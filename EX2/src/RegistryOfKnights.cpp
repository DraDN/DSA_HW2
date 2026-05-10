#include "RegistryOfKnights.hpp"

tools::Optional<RK::Knight> RK::RegistryOfKnights::remove(const char* name) {
    tools::Optional<Knight> search_result = registry.findLinear([&](const Knight& k){
        return strcmp(k.name, name) == 0;
    });

    if (!search_result) return tools::nullopt;

    registry.remove(*search_result);
    return search_result;
}

void RK::RegistryOfKnights::tournamentRankingScroll(std::ostream &os) const {
    registry.traverseInOrder([&](const Knight& k){
        os << k.name << "(" << k.braveryScore << ")\n";
    });
}

void RK::RegistryOfKnights::royalProclamationOrder(std::ostream &os) const {
    registry.traversePreOrder([&](const Knight& k){
        os << k.name << "(" << k.battlesWon << ")\n";
    });
}

void RK::RegistryOfKnights::tributeCollectionOrder(std::ostream &os) const {
    registry.traversePostOrder([&](const Knight& k){
        os << k.name << "(" << k.battlesWon << ")\n";
    });
}

void RK::RegistryOfKnights::getKnightsOfHouse(const char *house, tools::Queue<Knight> &knights) const {
    registry.traverseInOrder([&](const Knight& k){
        if (strcmp(k.house, house) == 0) knights.enqueue(k);
    });
}

tools::Optional<RK::Knight> RK::RegistryOfKnights::getLowestCommonAncestor(const char* name1, const char* name2) const {
    tools::Optional<Knight> search_result1 = registry.findLinear([&](const Knight& k){
        return strcmp(k.name, name1) == 0;
    });

    tools::Optional<Knight> search_result2 = registry.findLinear([&](const Knight& k){
        return strcmp(k.name, name2) == 0;
    });

    if (!search_result1 || !search_result2) return tools::nullopt;
    return registry.getLowestCommonAncestor(*search_result1, *search_result2);
}
