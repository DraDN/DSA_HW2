#include "CityController.hpp"
#include <cstring>

void rrm::CityController::handleInsertLocation(int countLocation) {
    if (countLocation <= 0) {
        out << "Invalid number of locations.\n" << std::endl;
        return;
    }

    for (int i = 0; i < countLocation; i++) {
        out << "Location " << (i + 1) << " of " << countLocation << " name: ";
        char locationName[100];
        in.getline(locationName, 100);
        cityGraph.insertLocation(locationName);
    }
}

void rrm::CityController::handleInsertRoute(int countRoute) {
    if (countRoute <= 0) {
        out << "Invalid number of routes.\n" << std::endl;
        return;
    }

    for (int i = 0; i < countRoute; i++) {
        out << "Route " << (i + 1) << " of " << countRoute << " (from to time risk energy): ";
        char fromLocation[100], toLocation[100];
        int timeDuration, riskLvl, energyDrain;
        in >> fromLocation >> toLocation >> timeDuration >> riskLvl >> energyDrain;
        in.ignore();
        cityGraph.insertRoute(fromLocation, toLocation, timeDuration, riskLvl, energyDrain);
    }
}

void rrm::CityController::handleAssignChargingStation(int countChargingSt) {
    if (countChargingSt < 0) {
        out << "Invalid number of charging stations.\n" << std::endl;
        return;
    }

    for (int i = 0; i < countChargingSt; i++) {
        out << "Charging station " << (i + 1) << " of " << countChargingSt << " location name: ";
        char locationName[100];
        in.getline(locationName, 100);
        cityGraph.assignChargingStation(locationName);
    }
}

void rrm::CityController::handleAssignCriticalZone(int countCriticalZn) {
    if (countCriticalZn < 0) {
        out << "Invalid number of critical zones.\n" << std::endl;
        return;
    }

    for (int i = 0; i < countCriticalZn; i++) {
        out << "Critical zone " << (i + 1) << " of " << countCriticalZn << " location name: ";
        char locationName[100];
        in.getline(locationName, 100);
        cityGraph.assignCriticalZone(locationName);
    }
}

void rrm::CityController::printCityMap() {
    cityGraph.printCityMap(out);
    out << std::endl;
}

void rrm::CityController::handleFindMostExposedArea() {
    cityGraph.findMostExposedArea(out);
    out << std::endl;
}

void rrm::CityController::handleCheckGlobalValidity() {
    if (cityGraph.isGloballyValid()) {
        out << "The network is valid when the road directions are ignored." << std::endl;
    } else {
        out << "The network is not valid, disconnected components found." << std::endl;
    }
    out << std::endl;
}

void rrm::CityController::handleDisplayBlockedAreas() {
    cityGraph.displayBlockedAreas(out);
    out << std::endl;
}

void rrm::CityController::handleFindUnreachableAreas() {
    out << "Enter base location name: ";
    char baseLocation[100];
    in >> baseLocation;
    in.ignore();
    cityGraph.findUnreachableAreas(baseLocation, out);
    out << std::endl;
}

void rrm::CityController::handleSolvePathForRobot() {
    out << "Enter deployment point, autonomy energy, max risk: ";
    char deploymentPoint[100];
    int autonomyEnergy, maximumRisk;
    if (in >> deploymentPoint >> autonomyEnergy >> maximumRisk) {
        in.ignore();
        Robot robot(deploymentPoint, autonomyEnergy, maximumRisk);
        cityGraph.solvePathForRobot(robot, out);
    }
    out << std::endl;
}

void rrm::CityController::handleSolvePathForRobots(int count) {
    for (int robotNr = 0; robotNr < count; robotNr++) {
        out << " Robot " << (robotNr + 1) << " of " << count
            << " (start   autonomy   max risk): ";
        char deploymentPoint[100];
        int autonomyEnergy, maximumRisk;
        if (in >> deploymentPoint >> autonomyEnergy >> maximumRisk) {
            in.ignore();
            out << "Robot " << (robotNr + 1) << ":\n";
            out << "Initial position: " << deploymentPoint << "\n";
            out << "Autonomy: " << autonomyEnergy << "\n";
            out << "Maximum accepted risk: " << maximumRisk << "\n";
            Robot robot(deploymentPoint, autonomyEnergy, maximumRisk);
            cityGraph.solvePathForRobot(robot, out);
        }
        out << std::endl;
    }
}
