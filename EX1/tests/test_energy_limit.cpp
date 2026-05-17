#include "CityGraph.hpp"
#include "RobotRoadModel.hpp"
#include <sstream>
#include <iostream>
 
static int passed = 0, failed = 0;
static void check(bool ok, const char* name) {
    std::cout << (ok ? "  [PASS] " : "  [FAIL] ") << name << "\n";
    ok ? passed++ : failed++;
}
static bool has(const std::string& s, const std::string& sub) {
    return s.find(sub) != std::string::npos;
}
 
int main() {
    { rrm::CityGraph smallCity(10);
      smallCity.insertLocation("Base"); 
      smallCity.insertLocation("Hospital");

      smallCity.insertRoute("Base","Hospital",8,1,4); 
      smallCity.assignCriticalZone("Hospital");

      std::ostringstream out; rrm::Robot robot1("Base",10,5);
      smallCity.solvePathForRobot(robot1,out);
      check(has(out.str(),"Hospital") && has(out.str(),"8"), "direct single hop: reaches Hospital in 8 min"); }
 
    { rrm::CityGraph smallCity(10);
      smallCity.insertLocation("Base"); 
      smallCity.insertLocation("Hospital"); 
      smallCity.insertLocation("School");

      smallCity.insertRoute("Base","Hospital", 3,1,2);
      smallCity.insertRoute("Hospital","School",  3,1,2);
      smallCity.insertRoute("Base","School",20,1,1); 
      smallCity.assignCriticalZone("School");

      std::ostringstream out; rrm::Robot robot2("Base",10,5);
      smallCity.solvePathForRobot(robot2,out);
      check(has(out.str(),"Hospital"), "shortest-time path goes through Hospital, not direct 20-min road"); }
 
    { rrm::CityGraph smallCity(10);
      smallCity.insertLocation("Base");
      smallCity.insertLocation("ChargingSt"); 
      smallCity.insertLocation("School");

      smallCity.insertRoute("Base",  "ChargingSt",5,1,8);
      smallCity.insertRoute("ChargingSt","School",   5,1,8);
      smallCity.insertRoute("Base",  "School",  10,1,15); 
      smallCity.assignChargingStation("ChargingSt"); 
      smallCity.assignCriticalZone("School");

      std::ostringstream out; rrm::Robot robot3("Base",10,5);
      smallCity.solvePathForRobot(robot3,out);
      check(has(out.str(),"ChargingSt") && !has(out.str(),"No valid"), "recharge used when direct path costs too much energy"); }
 
    { rrm::CityGraph smallCity(10);
      smallCity.insertLocation("Base"); 
      smallCity.insertLocation("Station"); 
      smallCity.insertLocation("School");

      smallCity.insertRoute("Base",  "Station",5,1,9);
      smallCity.insertRoute("Station","School",   5,1,9);  
      smallCity.assignChargingStation("Station"); 
      smallCity.assignCriticalZone("School");

      std::ostringstream out; rrm::Robot robot4("Base",9,5);
      smallCity.solvePathForRobot(robot4,out);
      check(has(out.str(),"School") && !has(out.str(),"No valid"), "energy resets at station, each leg uses full autonomy budget"); }
 
    { rrm::CityGraph smallCity(10);
      smallCity.insertLocation("Base"); 
      smallCity.insertLocation("ChargingSt"); 
      smallCity.insertLocation("School");

      smallCity.insertRoute("ChargingSt","School",5,1,3);
      smallCity.assignChargingStation("ChargingSt"); 
      smallCity.assignCriticalZone("School");

      std::ostringstream out; rrm::Robot robot5("Base",2,5);
      smallCity.solvePathForRobot(robot5,out);
      check(has(out.str(),"No valid"), "no solution when station is unreachable"); }
 
    { rrm::CityGraph smallCity(20);
      smallCity.insertLocation("Base"); 
      smallCity.insertLocation("Hospital");
      smallCity.insertLocation("Depot");   
      smallCity.insertLocation("School");

      smallCity.insertRoute("Base","Hospital",3,1,4); 
      smallCity.insertRoute("Hospital","School",3,1,4);
      smallCity.insertRoute("Base","Depot", 8,1,4); 
      smallCity.insertRoute("Depot", "School",2,1,4);
      smallCity.assignChargingStation("Hospital"); 
      smallCity.assignChargingStation("Depot");
      smallCity.assignCriticalZone("School");

      std::ostringstream out; rrm::Robot robot6("Base",5,5);
      smallCity.solvePathForRobot(robot6,out);
      check(has(out.str(),"Hospital") && !has(out.str(),"Depot"), "picks station giving minimum total travel time"); }
 
    std::cout << "\nResults: " << passed << " passed, " << failed << " failed\n";
    return failed == 0 ? 0 : 1;
}