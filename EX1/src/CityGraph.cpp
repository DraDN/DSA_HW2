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

    bool allReachableAreas = true;
    for (int i = 0; i < currentLocationCount; i++) {
        if (!visited[i]) {
            os << "Unreachable Area: " << locationList[i].locationName << "\n";
            allReachableAreas = false;
        }
    }

    if (allReachableAreas) {
        os << "All areas are reachable from the base location.\n";
    }

    delete[] visited;
    delete[] traversalPipeline;
    
}

//F, G
void rrm::CityGraph::solvePathForRobot(const Robot& robot, std::ostream& os) const {
        robot.deploymentPoint;
        robot.autonomyEnergy;
        robot.maximumRisk;

        int startIndex = findLocationIndex(robot.deploymentPoint);
        if (startIndex == -1) {
            os << "No valid direct path to a critical zone.\n";
            os << "No valid solution even with recharging.\n";
            return;
        }

        //Djikstra
        int* minimumTimeCost = new int[currentLocationCount];
        int* energyDrainage = new int[currentLocationCount];
        int* pathPredecessor = new int[currentLocationCount];
        bool* trackerVisitedLocations = new bool[currentLocationCount];

        auto executeDjikstraAlgorithm = [&](int startIndex) {
            for (int i = 0; i < currentLocationCount; i++) {
                minimumTimeCost[i] = INT_MAX;
                energyDrainage[i] = 0;
                pathPredecessor[i] = -1;
                trackerVisitedLocations[i] = false;
            }

            minimumTimeCost[startIndex] = 0;
            energyDrainage[startIndex] = 0;

            for (int countCost = 0; countCost < currentLocationCount - 1; countCost++) {
                int minCostVertex = -1;
                int minCostValue = INT_MAX;

                for (int vertexLocation = 0; vertexLocation < currentLocationCount; vertexLocation++) {
                    if (!trackerVisitedLocations[vertexLocation] && minimumTimeCost[vertexLocation] < minCostValue) {
                        minCostValue = minimumTimeCost[vertexLocation];
                        minCostVertex = vertexLocation;
                    }
                }

                if (minCostVertex == -1) break;

                trackerVisitedLocations[minCostVertex] = true;

                for (int neighbor = 0; neighbor < currentLocationCount; neighbor++) {
                    if (hasRoute[minCostVertex][neighbor]) {
                        const Road& roadToNeighbor = routeMatrix[minCostVertex][neighbor];

                        if (!trackerVisitedLocations[neighbor] && minimumTimeCost[minCostVertex] != INT_MAX) {
                            int potentialTimeCost = minimumTimeCost[minCostVertex] + roadToNeighbor.timeDuration;

                            if (potentialTimeCost < minimumTimeCost[neighbor]) {
                                minimumTimeCost[neighbor] = potentialTimeCost;
                                energyDrainage[neighbor] = energyDrainage[minCostVertex] + roadToNeighbor.energyDrain;
                                pathPredecessor[neighbor] = minCostVertex;
                            }

                        }
                    }
                }
            }
        };
    //F
    executeDjikstraAlgorithm(startIndex);

    int bestCriticalZoneIndex = -1;
    int bestTimeCost = INT_MAX;

    for (int i = 0; i < currentLocationCount; i++) {
        if (locationList[i].isCriticalzone && minimumTimeCost[i] != INT_MAX) {
            if (energyDrainage[i] <= robot.autonomyEnergy && minimumTimeCost[i] < bestTimeCost) {
                bestTimeCost = minimumTimeCost[i];
                bestCriticalZoneIndex = i;
            }
        }
        
    }

    if (bestCriticalZoneIndex != -1) {
        os << "Optimal path to critical zone: \n";

        int* pathStackSequence = new int[currentLocationCount];
        int* segmentCount = 0;
        int traceVertexIndex = bestCriticalZoneIndex;

        while (traceVertexIndex != -1) {
            pathStackSequence[*(segmentCount)++] = traceVertexIndex;
            traceVertexIndex = pathPredecessor[traceVertexIndex];
        }

        for (int i = (*segmentCount) - 1; i >= 0; i--) {
            os << locationList[pathStackSequence[i]].locationName;
            if (i > 0) {
                os << " -> ";
            }
        }

        os << "\nTotal Time: " << bestTimeCost << " minutes\n";
        os << "Total Energy Drain: " << energyDrainage[bestCriticalZoneIndex] << " units\n";
        os << "critical zone reached: " << locationList[bestCriticalZoneIndex].locationName << "\n";

        delete[] pathStackSequence;

    }
    else {
        //G
        os << "No valid direct path to a critical zone.\n";

        int bestRechargeZoneIndex = -1;
        int absoluteBestTotalTime = INT_MAX;
        int totalEnergyforBestPath = 0;

        for (int rechargeIndex = 0; rechargeIndex < currentLocationCount; rechargeIndex++) {
            if (locationList[rechargeIndex].isChargingStation && minimumTimeCost[rechargeIndex] != INT_MAX) {
                int timeToRecharge = minimumTimeCost[rechargeIndex];
                int energyToRecharge = energyDrainage[rechargeIndex];

                int* intermediateParents = new int[currentLocationCount];
                for (int i = 0; i < currentLocationCount; i++) {
                    intermediateParents[i] = pathPredecessor[i];
                }

                executeDjikstraAlgorithm(rechargeIndex);

                for ( int targetCriticalIndex = 0; targetCriticalIndex < currentLocationCount; targetCriticalIndex++) {
                    if (locationList[targetCriticalIndex].isCriticalzone && minimumTimeCost[targetCriticalIndex] != INT_MAX) {
                        int timeFromRechargeToCritical = timeToRecharge + minimumTimeCost[targetCriticalIndex];

                        if (timeFromRechargeToCritical < absoluteBestTotalTime) {
                            absoluteBestTotalTime = timeFromRechargeToCritical;
                            bestRechargeZoneIndex = rechargeIndex;
                            totalEnergyforBestPath = energyToRecharge + energyDrainage[targetCriticalIndex];
                        }
                    }
                }
                delete[] intermediateParents;
            }
        }

        if (bestRechargeZoneIndex != -1 && bestRechargeZoneIndex != -1) {
            os << "Optimal path with recharging: \n";


            executeDjikstraAlgorithm(startIndex);
            int* pathRechargeSequence = new int[currentLocationCount];
            int* segmentCountRecharge = 0;
            int traceVertexIndexRecharge = bestRechargeZoneIndex;

            while (traceVertexIndexRecharge != -1) {
                pathRechargeSequence[(*segmentCountRecharge)++] = traceVertexIndexRecharge;
                traceVertexIndexRecharge = pathPredecessor[traceVertexIndexRecharge];
            }

            executeDjikstraAlgorithm(bestRechargeZoneIndex);
            int* pathCriticalSequence = new int[currentLocationCount];
            int* segmentCountCritical = 0;
            int traceVertexIndexCritical = bestRechargeZoneIndex;

            while (traceVertexIndexCritical != -1) {
                pathCriticalSequence[(*segmentCountCritical)++] = traceVertexIndexCritical;
                traceVertexIndexCritical = pathPredecessor[traceVertexIndexCritical];
            }

            for (int i = (*segmentCountRecharge) - 1; i >= 0; i--) {
                os << locationList[pathRechargeSequence[i]].locationName << "->";
            }
            for (int i = (*segmentCountCritical) - 2; i >= 0; i--) {
                os << locationList[pathCriticalSequence[i]].locationName;
                if (i > 0) {
                    os << " -> ";   
                }
            }

            os << "\nTotal Time: " << absoluteBestTotalTime << " minutes\n";
            os << "Total Energy Drain: " << totalEnergyforBestPath << " units\n";
            os << "critical zone reached: " << locationList[bestRechargeZoneIndex].locationName << "\n";

            delete[] pathRechargeSequence;
            delete[] pathCriticalSequence;
        }
        else {
            os << "No valid solution even with recharging.\n";
        }
        
    }

    delete[] minimumTimeCost;
    delete[] energyDrainage;
    delete[] pathPredecessor;
    delete[] trackerVisitedLocations;


}







