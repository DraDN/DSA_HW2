#include "RegistryOfKnightsUI.hpp"

void RK::RegistryOfKnightsUI::handleInsert() {
    int n;
    in >> n;

    if (n < 0) {
        out << "Invalid input, enter a positive number for size!\n";
        return;
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        char name[256], house[256];
        int braveryScore, battlesWon;

        in >> name >> braveryScore >> house >> battlesWon;

        if (battlesWon < 0) {
            out << "Invalid input, enter a positive number for battles won for knight " << i << " from input!\n";
            return;
        }

        int insert_result = registry.insert(name, braveryScore, battlesWon, house);

        if (insert_result == 1) {
            out << "Knight with bravery score " << braveryScore << " already exists!\n";
            continue;
        } else if (insert_result == 2) {
            out << "Knight with name " << name << " already exists!\n";
            continue;
        } else {
            count++;
        }
    }

    out << "Successfully inserted " << count << " knights!\n";
}

void RK::RegistryOfKnightsUI::handleRemove() {
    char name[256];
    in >> name;

    tools::Optional<Knight> result = registry.remove(name);
    if (!result) {
        out << "Knight with name " << name << " not found!\n";
        return;
    }

    out << result->name << " (bravery: " << result->braveryScore << ") has been banished from the Registry.\n";
    out << "\nRegistry after banishment:\n";
    registry.tournamentRankingScroll(out);
}

void RK::RegistryOfKnightsUI::handleSearchByHouse() {
    char house[256];
    in >> house;

    tools::Queue<Knight> knights;
    registry.getKnightsOfHouse(house, knights);

    if (knights.isEmpty()) {
        out << "No knights from house " << house << " found!\n";
        return;
    }

    out << "Knights from house " << house << ":\n";
    while (!knights.isEmpty()) {
        auto temp_knight = knights.dequeue();
        out << temp_knight->name << " | bravery: " << temp_knight->braveryScore << " | battles won: " << temp_knight->battlesWon << "\n";
    }
}

void RK::RegistryOfKnightsUI::handleSearchByRange() {
    int minBravery, maxBravery;
    in >> minBravery >> maxBravery;

    if (minBravery > maxBravery) {
        out << "Invalid input, minBravery must be less than maxBravery!\n";
        return;
    }

    tools::Queue<Knight> knights;
    registry.getKnightsByBravery(minBravery, maxBravery, knights);

    if (knights.isEmpty()) {
        out << "No knights with bravery between " << minBravery << " and " << maxBravery << " found!\n";
        return;
    }

    out << "Knights with bravery in [" << minBravery << ", " << maxBravery << "]:\n\n";
    unsigned int sum = 0;
    while (!knights.isEmpty()) {
        auto temp_knight = knights.dequeue();
        sum += temp_knight->battlesWon;
        out << temp_knight->name << " (" << temp_knight->braveryScore << ") | House " << temp_knight->house << " | " << temp_knight->battlesWon << " battles\n";
    }

    out << "\nTotal battles won by knights in range: " << sum << "\n";
}

void RK::RegistryOfKnightsUI::printNewRecruit() {
    tools::Optional<Knight> result = registry.getNewestRecruit();
    if (!result) {
        out << "No knights in tree!\n";
        return;
    }

    out << "Newest Recruit (lowest bravery): " << result->name << " | bravery: " << result->braveryScore << " | " << result->house << " | " << result->battlesWon << " battles\n";
}

void RK::RegistryOfKnightsUI::printChampionOfTheRealm() {
    tools::Optional<Knight> result = registry.getChampionOfTheRealm();
    if (!result) {
        out << "No knights in tree!\n";
        return;
    }

    out << "Champion of the Realm (highest bravery): " << result->name << " | bravery: " << result->braveryScore << " | " << result->house << " | " << result->battlesWon << " battles\n";
}

void RK::RegistryOfKnightsUI::printKthValoredKnight() {
    unsigned int k;
    in >> k;

    tools::Optional<Knight> result = registry.getKthValoredKnight(k);
    if (!result) {
        out << "Not enough knights in tree!\n";
        return;
    }

    out << k << "th valored knight: " << result->name << " | bravery: " << result->braveryScore << " | House " << result->house << " | " << result->battlesWon << " battles\n";
}

void RK::RegistryOfKnightsUI::printLowestCommonAncestor() {
    char name1[256], name2[256];
    in >> name1 >> name2;

    if (strcmp(name1, name2) == 0) {
        out << "Invalid input, knight names must be different!\n";
        return;
    }

    tools::Optional<Knight> result = registry.getLowestCommonAncestor(name1, name2);
    if (!result) {
        // out << "No knights with names " << name1 << " and " << name2 << " found!\n";
        return;
    }

    out << "LCA of " << name1 << " and " << name2 << ":\n";
    out << result->name << " | bravery: " << result->braveryScore << "\n";
}

void RK::RegistryOfKnightsUI::printRegistryInfo() {
    out << "Height of the Archive: " << registry.getHeight() << "\n";

    tools::Queue<Knight> leafs;
    registry.getLeafs(leafs);

    out << "Leaf nodes (knights with no subordinates): " << leafs.getSize() << "\n";
    while (!leafs.isEmpty()) {
        auto temp_knight = leafs.dequeue();
        out << temp_knight->name << " (" << temp_knight->braveryScore << "), ";
    }
    out << "\n";

    if (registry.isBalanced()) {
        out << "The Archive is balanced.\n";
    } else {
        out << "The Archive is not balanced.\n";
    }
}
