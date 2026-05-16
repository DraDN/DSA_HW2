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

void rrm::CityGraph::printCityMap(std::ostream& os) const {
    for (int i = 0; i < currentLocationCount; i++) {
        os << "Location: " << locationList[i].locationName;
        if (locationList[i].isChargingStation) os << " (Charging Station)";
        if (locationList[i].isCriticalzone) os << " (Critical Zone)";
        os << "\n";

        bool hasRoads = false;
        for (int j = 0; j < currentLocationCount; j++) {
            if (hasRoute[i][j]) {
                os << "  -> " << locationList[j].locationName << " (Time: " << routeMatrix[i][j].timeDuration << " min, Risk: " << routeMatrix[i][j].riskLvl << ", Energy Drain: " << routeMatrix[i][j].energyDrain << " units)\n";
                hasRoads = true;
            }
            
        }
        if (!hasRoads) {
            os << "No outgoing roads.\n";
        } 
        
    }
}

//B
void rrm::CityGraph::findMostExposedArea(std::ostream& os) const {
    int* inDegrees = new int[currentLocationCount];
    for (int i = 0; i < currentLocationCount; i++) {
        inDegrees[i] = 0;
    }

    for (int i = 0; i < currentLocationCount; i++) {
        for (int j = 0; j < currentLocationCount; j++) {
            if (hasRoute[i][j]) {
                inDegrees[j]++;
            }
        }

    }

    int maxInDegree = -1;
    for (int i = 0; i < currentLocationCount; i++) {
        if (inDegrees[i] > maxInDegree) {
            maxInDegree = inDegrees[i];
        }
    }

    os << "Most exposed area(s):\n";
    for (int i = 0; i < currentLocationCount; i++) {
        if (inDegrees[i] == maxInDegree) {
            os << locationList[i].locationName << " with " << maxInDegree << " incoming roads\n";
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

    int* visitedLocations = new int[currentLocationCount];
    int head = 0;
    int tail = 0;

    reachLocations[0] = true;
    visitedLocations[tail++] = 0;

    while (head < tail) {
        int currentLocation = visitedLocations[head++];

        for (int neighbor = 0; neighbor < currentLocationCount; neighbor++) {
            if (!reachLocations[neighbor]) {
                if (hasRoute[currentLocation][neighbor] || hasRoute[neighbor][currentLocation]) {
                    reachLocations[neighbor] = true;
                    visitedLocations[tail++] = neighbor;
                }
            }
        }
    }

    bool componentsGloballyValid = true;
    for (int i = 0; i < currentLocationCount; i++) {
        if (!reachLocations[i]) {
            componentsGloballyValid = false;
            break;
        }
    }

    delete[] reachLocations;
    delete[] visitedLocations;

    return componentsGloballyValid;

}

//D
void rrm::CityGraph::displayBlockedAreas(std::ostream& os) const {
    os << "Blocked area(s):\n";
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
        if (inDegree > 0 && outDegree == 0) {
            if (hasBlockedAreas) {
                os << ", ";
            }
            os << locationList[i].locationName;
            hasBlockedAreas = true;
        }
    }
    if (!hasBlockedAreas) {
        os << "No blocked areas found.\n";
    }
    os << std::endl;
}

//E
void rrm::CityGraph::findUnreachableAreas(const char* base, std::ostream& os) const {
    int baseVertexIndex = findLocationIndex(base);
    if (baseVertexIndex == -1) {
        os << "Base location not found.\n";
        return;
    }

    bool* visited = new bool[currentLocationCount];
    for (int i = 0; i < currentLocationCount; i++) {
        visited[i] = false;
    }

    int* traversalPipeline = new int[currentLocationCount];
    int headPipe = 0;
    int tailPipe = 0;

    visited[baseVertexIndex] = true;
    traversalPipeline[tailPipe++] = baseVertexIndex;

    while (headPipe < tailPipe) {
        int currentLocation = traversalPipeline[headPipe++];

        for (int neighbor = 0; neighbor < currentLocationCount; neighbor++) {
            if (hasRoute[currentLocation][neighbor] && !visited[neighbor]) {
                visited[neighbor] = true;
                traversalPipeline[tailPipe++] = neighbor;
            }
        }
    }

    bool allUneachableAreas = false;
    os << "From base " << base << ", the following areas are unreachable: ";
    for (int i = 0; i < currentLocationCount; i++) {
        if (!visited[i]) {
            if (allUneachableAreas) {
                os << ", ";
            }
            os << locationList[i].locationName;
            allUneachableAreas = true;
        }
    }

    if (!allUneachableAreas) {
        os << "All areas are reachable from the base location.\n";
    }
    os << std::endl;

    delete[] visited;
    delete[] traversalPipeline;
    
}

//F, G
void rrm::CityGraph::solvePathForRobot(const Robot& robot, std::ostream& os) const {

    int startLocationIndex = findLocationIndex(robot.deploymentPoint);
    if (startLocationIndex == -1) return;

    int* minimumTimeCost = new int[currentLocationCount];
    int* energyDrainage = new int[currentLocationCount];
    int* pathPredecessor = new int[currentLocationCount];
    bool* trackerVisitedLocations = new bool[currentLocationCount];

    for (int i = 0; i < currentLocationCount; i++) {
        minimumTimeCost[i] = INT_MAX;
        energyDrainage[i] = INT_MAX;
        pathPredecessor[i] = -1;
        trackerVisitedLocations[i] = false;
    }

    minimumTimeCost[startLocationIndex] = 0;
    energyDrainage[startLocationIndex] = 0;

    for (int countCost = 0; countCost < currentLocationCount - 1; countCost++) {
        int minCostVertex = -1;
        int minCostValue = INT_MAX;

        for (int vertexLocation = 0; vertexLocation < currentLocationCount; vertexLocation++) {
            if (!trackerVisitedLocations[vertexLocation] && minimumTimeCost[vertexLocation] < minCostValue) {
                minCostValue = minimumTimeCost[vertexLocation];
                minCostVertex = vertexLocation;
            }
        }

        if (minCostVertex == -1 || minimumTimeCost[minCostValue == INT_MAX]) break;
        trackerVisitedLocations[minCostVertex] = true;

        for (int neighbor = 0; neighbor < currentLocationCount; neighbor++) {
                if (hasRoute[minCostVertex][neighbor] && !trackerVisitedLocations[neighbor]) {
                    const Road& roadToNeighbor = routeMatrix[minCostVertex][neighbor];

                    if(roadToNeighbor.riskLvl <= robot.maximumRisk){
                        int evaluatedEnergy = energyDrainage[minCostVertex] + roadToNeighbor.timeDuration;

                        if (evaluatedEnergy <= robot.autonomyEnergy) {
                            int potentialTime = minimumTimeCost[minCostVertex] + roadToNeighbor.timeDuration;

                            if (potentialTime < minimumTimeCost[neighbor] || (potentialTime == minimumTimeCost[neighbor] && evaluatedEnergy < energyDrainage[neighbor])) {
                                minimumTimeCost[neighbor] = potentialTime;
                                energyDrainage[neighbor] = evaluatedEnergy;
                                pathPredecessor[neighbor] = minCostVertex;
                            }
                        }

                    }
                }
            }
        }
        

    }

    //F
    int bestCriticalZoneIndex = -1;
    int bestTimeCost = INT_MAX;
    int bestEnergyCost = INT_MAX;

    for (int i = 0; i < currentLocationCount; i++) {
        if (locationList[i].isCriticalzone && minimumTimeCost[i] != INF) {
            if (minimumTimeCost[i] < bestTimeVCost || (minimumTimeCost[i] == bestTimeCost && energyDrainage[i] < bestEnergyCost)) {
                bestTimeCost = minimumTimeCost[i];
                bestEnergyCost = energyDrainage[i];
                bestCriticalZoneIndex = i;
            }
        }
    }
    
    if (bestCriticalZoneIndex != -1) {
        os < "Optimal direct path to a critical zone: \n";
        int* traceBuffer = new int[currentLocationCount];
        int hopsCrZn= 0;
        int currentCrZn = bestCriticalZoneIndex;
        while (currentCrZn != -1) {
            traceBuffer[hopsCrZn++] = currentCrZn;
            currentCrZn = pathPredecessor[currentCrZn];
        }

        for (int i = hopsCrZn -1; i >= 0; i--) {
            os << loctionList[traceBuffer[i]].locationName;
            if (i > 0) os << " -> ";
        }
        
        os << "\nTotal travel time: " << bestTimeCost << "\n";
        os << "Energy consumed " << bestEnergyCost << "\n";
        os << "Critical zone reached: " << locationList[bestCriticalZoneIndex].locationName << "\n";

        delete[] traceBuffer;

    } else {
        os << "No valid direct path to a critical zone.\n";

        int globalBestTime = INT_MAX;
        int optimalStationIndex = -1;
        int optimalTargetIndex = -1;
        int optimalEnergyPtI = INT_MAX;
        int optimalEnergyPtII = INT_MAX;

        for (int localStation = 0; localStation < currentLocalCount; localStation++) {
            if (!locationList[localStation].isChargingStation || minimumTimeCost[localStation] == INT_MAX) continue;

           /*int timeToStation = minTime[station];
            int energyToStation = energyCost[station];

            int* subTime = new int[currentLocationCount];
            int* subEnergy = new int[currentLocationCount];
            bool* subProcessed = new bool[currentLocationCount];

            for (int i = 0; i < currentLocationCount; i++) {
                subTime[i] = INF;
                subEnergy[i] = INF;
                subProcessed[i] = false;
            }

            subTime[station] = 0;
            subEnergy[station] = 0; */

        }
    }
}
        




