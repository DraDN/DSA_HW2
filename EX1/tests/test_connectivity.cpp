#include "CityGraph.hpp"
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
      check(smallCity.isGloballyValid(), "empty graph is valid"); }

    { rrm::CityGraph smallCity(10);
      smallCity.insertLocation("Hospital"); 
      smallCity.insertLocation("School"); 
      smallCity.insertLocation("Depot");

      smallCity.insertRoute("Hospital","School",1,1,1); 
      smallCity.insertRoute("School","Depot",1,1,1);

      check(smallCity.isGloballyValid(), "connected chain Hospital->School->Depot is valid"); }

    { rrm::CityGraph smallCity(10);
      smallCity.insertLocation("Hospital"); 
      smallCity.insertLocation("School");
      smallCity.insertLocation("Depot"); 
      smallCity.insertLocation("Market");

      smallCity.insertRoute("Hospital","School",1,1,1); 
      smallCity.insertRoute("Depot","Market",1,1,1);

      check(!smallCity.isGloballyValid(), "two isolated pairs are NOT valid"); }

    { rrm::CityGraph smallCity(10);
      smallCity.insertLocation("Hospital"); 
      smallCity.insertLocation("School"); 
      smallCity.insertLocation("Lone");

      smallCity.insertRoute("Hospital","School",1,1,1);

      check(!smallCity.isGloballyValid(), "isolated node makes graph NOT valid"); }

    { rrm::CityGraph smallCity(10);
      smallCity.insertLocation("Base"); 
      smallCity.insertLocation("Mid"); 
      smallCity.insertLocation("End");

      smallCity.insertRoute("Base","Mid",1,1,1); 
      smallCity.insertRoute("Mid","End",1,1,1);

      std::ostringstream out; smallCity.findUnreachableAreas("Base", out);
      check(has(out.str(),"reachable"), "all reachable from Base"); }

    { rrm::CityGraph smallCity(10);
      smallCity.insertLocation("Base"); 
      smallCity.insertLocation("Hospital"); 
      smallCity.insertLocation("Island");

      smallCity.insertRoute("Base","Hospital",1,1,1);

      std::ostringstream out; smallCity.findUnreachableAreas("Base", out);
      check(has(out.str(),"Island"), "Island is unreachable from Base"); }

    { rrm::CityGraph smallCity(10); 
      smallCity.insertLocation("Hospital");

      std::ostringstream out; smallCity.findUnreachableAreas("Ghost", out);
      check(has(out.str(),"not found"), "unknown base reports 'not found'"); }

    { rrm::CityGraph smallCity(10);
      smallCity.insertLocation("Hospital"); 
      smallCity.insertLocation("School");

      smallCity.insertRoute("Hospital","School",1,1,1);  
      
      std::ostringstream out; smallCity.findUnreachableAreas("School", out);
      check(has(out.str(),"Hospital"), "Hospital unreachable when starting from School (one way road)"); }

    std::cout << "\nResults: " << passed << " passed, " << failed << " failed\n";
    return failed == 0 ? 0 : 1;
}