#pragma once

#include <cstring>
#include <iostream>


namespace rrm {

    struct Robot {
        char* deploymentPoint = nullptr;
        int autonomyEnergy = 0;
        int maximumRisk = 0;

        Robot() {}

        Robot(const char* location, int autonomyEnergy, int maximumRisk) : autonomyEnergy(autonomyEnergy), maximumRisk(maximumRisk) {
            this->deploymentPoint = new char[strlen(location) + 1];
            strcpy(this->deploymentPoint, location);
        }

        ~Robot() {
            delete[] deploymentPoint;
        }

        Robot(const Robot& other) {
            autonomyEnergy = other.autonomyEnergy;
            maximumRisk = other.maximumRisk;
            deploymentPoint = other.deploymentPoint ? new char[strlen(other.deploymentPoint) + 1] : nullptr; 
            if (deploymentPoint) strcpy(deploymentPoint, other.deploymentPoint);
        }

        Robot& operator=(const Robot& other) {
            if (this != &other) { 
                delete[] deploymentPoint;
                autonomyEnergy = other.autonomyEnergy;
                maximumRisk = other.maximumRisk;
                deploymentPoint = other.deploymentPoint ? new char[strlen(other.deploymentPoint) + 1] : nullptr;
                if (deploymentPoint) strcpy(deploymentPoint, other.deploymentPoint);
            }
            return *this;
        }
        
    };

    struct Road {
        char* destionation = nullptr;
        int timeDuration = 0;
        int riskLvl = 0;
        int energyDrain = 0;

        Road() {}

        Road(const char* toArea, int timeDuration, int riskLvl, int energyDrain) : timeDuration(timeDuration), riskLvl(riskLvl), energyDrain(energyDrain) {
            this->destionation = new char[strlen(toArea) + 1];
            strcpy(this->destionation, toArea);
        }

        ~Road() {
            delete[] destionation;
        }

        Road(const Road& other) {
            timeDuration = other.timeDuration;
            riskLvl = other.riskLvl;
            energyDrain = other.energyDrain;
            destionation = other.destionation ? new char[strlen(other.destionation) + 1] : nullptr; 
            if (destionation) strcpy(destionation, other.destionation);
        }

        Road& operator=(const Road& other) {
            if (this != &other) { 
                delete[] destionation;
                timeDuration = other.timeDuration;
                riskLvl = other.riskLvl;
                energyDrain = other.energyDrain;
                destionation = other.destionation ? new char[strlen(other.destionation) + 1] : nullptr;
                if (destionation) strcpy(destionation, other.destionation);
            }
            return *this;
        }

    };

    struct Area {
        char* locationName = nullptr;
        bool isChargingStation = false;
        bool isCriticalzone = false;

        Road* roadLinks = nullptr;
        int numberRoadLinks = 0;

        Area() {}

        Area(const char* locationName) {
            this->locationName = new char[strlen(locationName) + 1];
            strcpy(this->locationName, locationName);
        }

        ~Area() {
            delete[] locationName;
            delete[] roadLinks;
        }


    };

}