#pragma once

#include "RegistryOfKnights.hpp"

void add_test_data(RK::RegistryOfKnights& registry) {
    registry.insert("Arthur", 50, 30, "Pendragon");
    registry.insert("Lancelot", 30, 45, "Lionel");
    registry.insert("Gawain", 70, 22, "Pendragon");
    registry.insert("Percival", 20, 15, "Fisher");
    registry.insert("Tristan", 40, 28, "Cornwall");
    registry.insert("Galahad", 60, 38, "Lionel");
    registry.insert("Bedivere", 80, 19, "Pendragon");
    registry.insert("Bors", 25, 12, "Lionel");
    registry.insert("Gareth", 55, 17, "Pendragon");
    registry.insert("Lamorak", 35, 33, "Cornwall");
}