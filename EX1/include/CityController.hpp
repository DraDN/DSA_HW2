#pragma once

#include "CityGraph.hpp"
#include <ostream>
#include <istream>

namespace rrm {

    class CityController {
        public:
            CityController(CityGraph& cityGraph, std::ostream& out, std::istream& in) : cityGraph(cityGraph), out(out), in(in) {}

            void handleInsertLocation(int countLocation);
            void handleInsertRoute(int countRoute);
            void handleAssignChargingStation(int countChargingSt);
            void handleAssignCriticalZone(int countCriticalZn);

            void printCityMap();

            void handleFindMostExposedArea();
            void handleCheckGlobalValidity();
            void handleDisplayBlockedAreas();
            void handleFindUnreachableAreas();
            void handleSolvePathForRobot();
            void handleSolvePathForRobots(int countRobots);


        private:
            CityGraph& cityGraph;
            std::ostream& out;
            std::istream& in;

    };
}