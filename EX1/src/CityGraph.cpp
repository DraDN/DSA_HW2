#include "CityGraph.hpp"
#include <cstring>

//A 
void rrm::CityGraph::insertLocation(const char* locationName) {
    if (currentLocationCount < capacity) {
        locationList[currentLocationCount] = Area(locationName);
        currentLocationCount++;
    }
}

void rrm::CityGraph::insertRoute(const char* fromLocation, const char* toLocation, int timeDuration, int riskLvl, int energyDrain) {
    int fromIndex = findLocationIndex(fromLocation);
    int toIndex = findLocationIndex(toLocation);

    if (fromIndex != -1 && toIndex != -1) {
        routeMatrix[fromIndex][toIndex] = Road(toLocation, timeDuration, riskLvl, energyDrain);
        hasRoute[fromIndex][toIndex] = true;
    }
}

void rrm::CityGraph::assignChargingStation(const char* locationName) {
    int indexCharge = findLocationIndex(locationName);
    if (indexCharge != -1) {
        locationList[indexCharge].isChargingStation = true;
    }
}

void rrm::CityGraph::assignCriticalZone(const char* locationName) {
    int indexCritical = findLocationIndex(locationName);
    if (indexCritical != -1) {
        locationList[indexCritical].isCriticalzone = true;
    }
}

//B
void rrm::CityGraph::findMostExposedArea(std::ostream& os) const {
    int maxInDegree = -1;
    int* inDegrees = new int[currentLocationCount];
    for (int i = 0; i < currentLocationCount; i++) {
        inDegrees[i] = 0;
        for (int j = 0; j < currentLocationCount; j++) {
            if (hasRoute[j][i]) {
                if (hasRoute[j][i]) {
                    inDegrees[i]++;
                }
            }
            if (inDegrees[i] > maxInDegree) {
                maxInDegree = inDegrees[i];
            }

        }
    }

    for (int i = 0; i < currentLocationCount; i++) {
        if (inDegrees[i] == maxInDegree) {
            os << "Most Exposed Area: " << locationList[i].locationName << " with " << maxInDegree << " incoming roads\n";
        }
    }

    delete[] inDegrees;

}

//C
bool rrm::CityGraph::isGloballyValid() const {
    if (currentLocationCount == 0) return true;

    bool* reachLocations = new bool[currentLocationCount]; 
    for (int i = 0; i < currentLocationCount; i++) {
        reachLocations[i] = false;
    }

    bool* visitedLocations = new bool[currentLocationCount];
    int head = 0;
    int tail = 0;

    reachLocations[0] = true;
    visitedLocations[tail++] = 0;
    int unifiedAreaCount = 1;

    while (head < tail) {
        int currentLocation = visitedLocations[head++];

        for (int neighbor = 0; neighbor < currentLocationCount; neighbor++) {
            bool hasRoad = hasRoute[currentLocation][neighbor] || hasRoute[neighbor][currentLocation];

            if (hasRoute && !reachLocations[neighbor]) {
                reachLocations[neighbor] = true;
                visitedLocations[tail++] = neighbor;
                unifiedAreaCount++;
            }
        }
    }

    bool isGloballyValid = (unifiedAreaCount == currentLocationCount);

    delete[] reachLocations;
    delete[] visitedLocations;

    return isGloballyValid;

}

//D
void rrm::CityGraph::displayBlockedAreas(std::ostream& os) const {
    bool hasBlockedAreas = false;
    for (int i = 0; i < currentLocationCount; i++) {
        int inDegree = 0;
        int outDegree = 0;

        for (int j = 0; j < currentLocationCount; j++) {
            if (hasRoute[j][i]) {
                inDegree++;
            }
            if (hasRoute[i][j]) {
                outDegree++;
            }
        }
        if (inDegree == 0 && outDegree > 0) {
            os << locationList[i].locationName << "\n";
            hasBlockedAreas = true;
        }
    }
    if (!hasBlockedAreas) {
        os << "No blocked areas found.\n";
    }
}

//E





