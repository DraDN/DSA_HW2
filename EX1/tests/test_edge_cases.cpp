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
    { rrm::CityGraph emptyGraph(10);
      check(emptyGraph.isGloballyValid(), "empty graph is valid"); }
 
    { rrm::CityGraph emptyGraph(10);
      std::ostringstream out; emptyGraph.displayBlockedAreas(out);
      check(has(out.str(),"No blocked"), "empty graph has no blocked areas"); }
 
    { rrm::CityGraph unknownNamesCity(10); 
      unknownNamesCity.insertLocation("Hospital");

      bool ok = true;
      try { unknownNamesCity.insertRoute("Hospital","Ghost",1,1,1); unknownNamesCity.insertRoute("Ghost","Hospital",1,1,1); }
      catch(...) { ok = false; }
      check(ok, "insertRoute with unknown name does not throw"); }
 
    { rrm::CityGraph unknownNamesCity(10);
      bool ok = true;
      try { unknownNamesCity.assignChargingStation("School"); unknownNamesCity.assignCriticalZone("School"); }
      catch(...) { ok = false; }
      check(ok, "assign to unknown location does not throw"); }

    { rrm::CityGraph unknownNamesCity(10);
      unknownNamesCity.insertLocation("Base"); 
      unknownNamesCity.insertLocation("Hospital");

      unknownNamesCity.insertRoute("Base","Hospital",1,1,1); 
      unknownNamesCity.assignCriticalZone("Hospital");

      std::ostringstream out; rrm::Robot robot1("Ghost",50,5);
      bool ok = true;
      try { unknownNamesCity.solvePathForRobot(robot1,out); } catch(...) { ok = false; }
      check(ok, "robot at unknown start does not throw"); }
 
    { rrm::CityGraph noTargetCity(10);
      noTargetCity.insertLocation("Base"); 
      noTargetCity.insertLocation("Hospital");

      noTargetCity.insertRoute("Base","Hospital",1,1,1);

      std::ostringstream out; rrm::Robot robot2("Base",50,5);
      noTargetCity.solvePathForRobot(robot2,out);
      check(has(out.str(),"No valid"), "no critical zones — no valid path"); }
 
    { rrm::CityGraph blockedCity(10);
      blockedCity.insertLocation("Entry"); 
      blockedCity.insertLocation("Trap");

      blockedCity.insertRoute("Entry","Trap",1,1,1); 

      std::ostringstream out; blockedCity.displayBlockedAreas(out);
      check(has(out.str(),"Trap") && !has(out.str(),"Entry"), "Trap is blocked, Entry is not"); }
 
    { rrm::CityGraph blockedCity(10);
      blockedCity.insertLocation("Island"); 

      std::ostringstream out; blockedCity.displayBlockedAreas(out);
      check(!has(out.str(),"Island"), "Island, isolated node is NOT a blocked area"); }
 
    { rrm::CityGraph exposedAreaCity(10);
      exposedAreaCity.insertLocation("Hospital"); 
      exposedAreaCity.insertLocation("School");
      exposedAreaCity.insertLocation("Depot");  
      exposedAreaCity.insertLocation("Market");

      exposedAreaCity.insertRoute("School","Hospital",1,1,1); 
      exposedAreaCity.insertRoute("Depot","Hospital",1,1,1);
      exposedAreaCity.insertRoute("Market","Hospital",1,1,1);

      std::ostringstream out; exposedAreaCity.findMostExposedArea(out);
      check(has(out.str(),"Hospital"), "Hospital identified as most exposed"); }
 
    std::cout << "\nResults: " << passed << " passed, " << failed << " failed\n";
    return failed == 0 ? 0 : 1;
}
 