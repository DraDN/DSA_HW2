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

static rrm::CityGraph buildRiskGraph() {
    rrm::CityGraph riskCity(10);
    riskCity.insertLocation("Start"); riskCity.insertLocation("Safe");
    riskCity.insertLocation("Risky"); riskCity.insertLocation("Target");
    riskCity.insertRoute("Start","Safe",  10,1,3); riskCity.insertRoute("Safe", "Target",10,1,3);
    riskCity.insertRoute("Start","Risky", 2, 10,1); riskCity.insertRoute("Risky","Target",2, 10,1);
    riskCity.assignCriticalZone("Target");
    return riskCity;
}
 
int main() {
    //risk
    { auto riskCity = buildRiskGraph();
      std::ostringstream out; rrm::Robot robot1("Start",20,10);
      riskCity.solvePathForRobot(robot1,out);
      check(has(out.str(),"Risky"), "high maxRisk robot uses faster risky road"); }
 
    { auto riskCity = buildRiskGraph();
      std::ostringstream out; rrm::Robot robot2("Start",20,3);
      riskCity.solvePathForRobot(robot2,out);
      check(!has(out.str(),"Risky") && has(out.str(),"Safe"), "low maxRisk robot avoids risky road, uses safe"); }
 
    { rrm::CityGraph riskCity(10);
      riskCity.insertLocation("Hospital"); 
      riskCity.insertLocation("School");

      riskCity.insertRoute("Hospital","School",5,9,2); 
      riskCity.assignCriticalZone("School");

      std::ostringstream out; rrm::Robot robot3("Hospital",100,2);
      riskCity.solvePathForRobot(robot3,out);
      check(has(out.str(),"No valid"), "no path when all roads exceed maxRisk"); }
 
    { rrm::CityGraph riskCity(10);
      riskCity.insertLocation("Hospital"); 
      riskCity.insertLocation("School");

      riskCity.insertRoute("Hospital","School",5,5,2); 
      riskCity.assignCriticalZone("School");

      std::ostringstream out; rrm::Robot robot4("Hospital",100,5);
      riskCity.solvePathForRobot(robot4,out);
      check(has(out.str(),"School"), "road with risk == maxRisk is accepted (boundary)"); }
 
    //energy
    { rrm::CityGraph riskCity(10);
      riskCity.insertLocation("Hospital"); 
      riskCity.insertLocation("School");

      riskCity.insertRoute("Hospital","School",5,1,10); 
      riskCity.assignCriticalZone("School");

      std::ostringstream out; rrm::Robot robot5("Hospital",10,5);
      riskCity.solvePathForRobot(robot5,out);
      check(has(out.str(),"School"), "robot with exact energy reaches target"); }
 
    { rrm::CityGraph riskCity(10);
      riskCity.insertLocation("Hospital"); 
      riskCity.insertLocation("School");

      riskCity.insertRoute("Hospital","School",5,1,10); 
      riskCity.assignCriticalZone("School");

      std::ostringstream out; rrm::Robot robot6("Hospital",9,5);
      riskCity.solvePathForRobot(robot6,out);
      check(has(out.str(),"No valid"), "robot with energy 9 cannot cross cost 10 road"); }
 
    { rrm::CityGraph riskCity(10);
      riskCity.insertLocation("Hospital"); 
      riskCity.insertLocation("School"); 
      riskCity.insertLocation("Depot");

      riskCity.insertRoute("Hospital","School",3,1,5); 
      riskCity.insertRoute("School","Depot",3,1,5);
      riskCity.assignCriticalZone("Depot");
      
      std::ostringstream out; rrm::Robot robot7("Hospital",9,5);
      riskCity.solvePathForRobot(robot7,out);
      check(has(out.str(),"No valid"), "cumulative energy 10 exceeds autonomy 9"); }
 
    std::cout << "\nResults: " << passed << " passed, " << failed << " failed\n";
    return failed == 0 ? 0 : 1;
}