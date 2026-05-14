#include "CityController.hpp"

void rrm::CityController::handleInsertLocation(int count) {
    for (int i = 0; i < count; i++) {
        char locationName[256];
        in >> locationName;
        cityGraph.insertLocation(locationName);
    }
}