#include "RobotRoadModel.hpp"
#include "CityGraph.hpp"
#include "CityController.hpp"

int main() {
    rrm::CityGraph cityCapacityLocations(50);
    rrm::CityController controllerCity(cityCapacityLocations, std::cout, std::cin);

    int totalCityLocations, totalCityRoutes;
    if(!(std::cin >> totalCityLocations >> totalCityRoutes)) return 0;
    std::cin.ignore();

    controllerCity.handleInsertLocation(totalCityLocations);
    controllerCity.handleInsertRoute(totalCityRoutes);


    int totalCityChargingStations;
    std::cin >> totalCityChargingStations;
    std::cin.ignore();
    controllerCity.handleAssignChargingStation(totalCityChargingStations);


    int totalCityCriticalZone;
    std::cin >> totalCityCriticalZone;
    std::cin.ignore();
    controllerCity.handleAssignCriticalZone(totalCityCriticalZone);


    controllerCity.handleFindMostExposedArea();

    controllerCity.handleCheckGlobalValidity();

    controllerCity.handleDisplayBlockedAreas();

    controllerCity.handleFindUnreachableAreas();

    controllerCity.handleSolvePathForRobot();

    return 0;
}