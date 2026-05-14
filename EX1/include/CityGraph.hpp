#pragma once

#include "RobotRoadModel.hpp"
#include <ostream>

namespace rrm {

    class CityGraph {
        public:
        CityGraph(int maximumLocations) : capacity(maximumLocations), currentLocationCount(0) {
            locationList = new Area[capacity];
            routeMatrix = new Road*[capacity];
            hasRoute = new bool*[capacity];

            for (int i = 0; i < capacity; i++) {
                routeMatrix[i] = new Road[capacity];
                hasRoute[i] = new bool[capacity];
                for (int j = 0; j < capacity; j++) {
                    hasRoute[i][j] = false;
                }
            }

        }

        ~CityGraph() {
            for (int i = 0; i < capacity; i++) {
                delete[] routeMatrix[i];
                delete[] hasRoute[i];
            }

            delete[] routeMatrix;
            delete[] hasRoute;
            delete[] locationList;
        }

        //A -data population
        void insertLocation(const char* locationName);
        void insertRoute(const char* fromLocation, const char* toLocation, int timeDuration, int riskLvl, int energyDrain);
        void assignChargingStation(const char* locationName);
        void assignCriticalZone(const char* locationName);

        void findMostExposedArea(std::ostream& os) const; //B

        bool isGloballyValid() const; //C

        void displayBlockedAreas(std::ostream& os) const; //D

        void findUnreachableAreas(const char* base, std::ostream& os) const; //E

        void solvePathForRobot(const Robot& robot, std::ostream& os) const; //F, G


        private:

        int findLocationIndex(const char* locationName) const{
            for (int i = 0; i < currentLocationCount; i++) {
                if (strcmp(locationList[i].locationName, locationName) == 0) {
                    return i;
                }
            }
            return -1;
        }

        Area* locationList;
        Road** routeMatrix;
        bool** hasRoute;

        int capacity;
        int currentLocationCount;

        Robot* squadRobots;
        int squadSize;

    };
}