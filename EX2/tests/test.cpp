#include "RegistryOfKnights.hpp"
#include "RegistryOfKnightsUI.hpp"

#include <iostream>
#include <fstream>

std::ifstream in("test.in");

RK::RegistryOfKnights registry;
RK::RegistryOfKnightsUI ui(registry, std::cout, in);

void task1() {
    ui.handleInsert();
}

void task2() {
    ui.printTournamentRanking();
    ui.printRoyalProclamationOrder();
    ui.printTributeCollectionOrder();
}

void task3() {
    ui.handleSearchByHouse();
    std::cout << "\n";
    ui.printNewRecruit();
    std::cout << "\n";
    ui.printChampionOfTheRealm();
}

void task4() {
    ui.printRegistryInfo();
}

void task5() {
    ui.handleSearchByRange();
}

void task6() {
    ui.printKthValoredKnight();
    std::cout << "\n";
    ui.printLowestCommonAncestor();
}

void task7() {
    ui.handleRemove();
}

int main() {
    void (*tasks[])() = {task1, task2, task3, task4, task5, task6, task7};

    if (!in.is_open()) {
        std::cout << "Could not open file!\n";
        return 1;
    }

    for (short i = 0; i < 7; i++) {
        std::cout << "=== " << i+1 << " ===\n";
        tasks[i]();
        std::cout << std::endl;
    }

    in.close();

    return 0;
}