#include "RobotRoadModel.hpp"
#include "CityGraph.hpp"
#include "CityController.hpp"
#include <sstream>

int main() {
    rrm::CityGraph cityCapacityLocations(50);
    rrm::CityController controllerCity(cityCapacityLocations, std::cout, std::cin);

    int totalCityLocations, totalCityRoutes;
    if(!(std::cin >> totalCityLocations >> totalCityRoutes)) return 0;
    std::cin.ignore();

    {
        std::string location;
        std::getline(std::cin, location);
        std::istringstream iss(location);
        std::string name;
        while (iss >> name) {
            cityCapacityLocations.insertLocation(name.c_str());
        }

    }

    controllerCity.handleInsertRoute(totalCityRoutes);
    
    {
        int charginStationVertex;
        std::cin >> charginStationVertex;
        std::cin.ignore();
        std::string station;
        std::getline(std::cin, station);
        std::istringstream iss(station);
        std::string name;
        while (iss >> name) {
            cityCapacityLocations.assignChargingStation(name.c_str());
        }
    }

    {
        int criticalZonevertex;
        std::cin >> criticalZonevertex;
        std::cin.ignore();
        std::string target;
        std::getline(std::cin, target);
        std::istringstream iss(target);
        std::string name;
        while (iss >> name) {
            cityCapacityLocations.assignCriticalZone(name.c_str());
        }


    }

    controllerCity.printCityMap();

    controllerCity.handleFindMostExposedArea();

    controllerCity.handleCheckGlobalValidity();

    controllerCity.handleDisplayBlockedAreas();

    int robotsCount;
    std::cin >> robotsCount;
    std::cin.ignore();

    controllerCity.handleSolvePathForRobots(robotsCount);

    controllerCity.handleFindUnreachableAreas();

    

    return 0;
}