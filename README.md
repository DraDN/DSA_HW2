# Data Strucutres and Algorithms - HW2

This repository contains solutions for the Data Structures and Algorithms Homework 2.
The homework focuses on the implementation and application graphs and binary search trees.

### Team Members - GROUP 1211EB

- Dragan Dragos-Nicolae
- Reculciuc Livia-Maria

## General information about the exercises

- Each exercise uses a different data structure type (graphs or binary search trees)
- The exercises are placed in separate folders and contain the .cpp and .hpp files
- The exercises use custom implementations and tools to manage memory cleanly and keep data structured

## Exercise 1 - Autonomous Intervention in a Damaged Urban Network

### Summary

This exercise creates a program to manage a map of a city for emergency robots. The program tracks locations, roads, charging stations, and critical safety zones (danger areas). It helps find the fastest and safest paths for robots to reach these danger zones during emergencies.

### Data Structure Used

***Graph (Adjency Matrix & Lists)***- Chosen because this structure holds vertices (areas) and edges (roads with travel time, risk, and energy costs). We used a 2D grid to quickly check if two locations are connected, how long the trip takes, how much energy it drains, and how risky the road is.

### Features

- Adds city locations, charging stations, and critical zones to the map
- Connects locations with roads that track time, risk, and energy cost
- Prints a clear map of the entire city showing all outgoing roads from each place
- Finds the "most exposed areas" (the locations with the most incoming roads
- Checks if the whole map is connected when ignoring road directions
- Finds "blocked areas" (dead-ends where you can enter but cannot leave)
- Finds "unreachable areas" that a robot cannot get to from a specific base location
- Calculates the best path for one or multiple robots based on their energy limits and maximum risk
- Automatically looks for a path with a recharge stop if a robot doesn't have enough energy to reach the target directly

### Implementation Details

- Uses simple objects (***Robot, Road, Area***) with custom memory rules to cleanly copy data and avoid memory leaks
- Uses a modified version of Dijkstra's Algorithm to find the fastest path, making sure the robot never exceeds its maximum risk level or runs out of battery
- Uses a menu loop in the controller to read user inputs easily from the console line by line

### Example

INPUT
```
9 13 //Number fo areas , number of roads
Base North East South West Hospital Depot School Center
Route 1 of 13 (from to time risk energy): Base North 4 2 3
Route 2 of 13 (from to time risk energy):  North East 3 1 2
Route 3 of 13 (from to time risk energy): East Hospital 5 3 4
Route 4 of 13 (from to time risk energy): Base South 6 2 5
Route 5 of 13 (from to time risk energy): South West 2 1 2
Route 6 of 13 (from to time risk energy): West Depot 4 2 3
Route 7 of 13 (from to time risk energy): Depot Hospital 3 2 2
Route 8 of 13 (from to time risk energy): North School 2 1 1
Route 9 of 13 (from to time risk energy): School Depot 6 3 5
Route 10 of 13 (from to time risk energy): Hospital Base 7 4 6
Route 11 of 13 (from to time risk energy): East Center 2 2 2
Route 12 of 13 (from to time risk energy): Center Hospital 2 1 1
Route 13 of 13 (from to time risk energy): South Center 4 3 3
3 //number of charging statons
Hospital Depot School
2 //number of critical zones
Hospital Center
Base //base point
3 //number of robots
 Base 8 2 //data robot 1
 South 6 1 //data robot 2
 West 4 2 //data robot 3
```

OUTPUT
```
Location: Base
  -> North (Time: 4 min, Risk: 2, Energy Drain: 3 units)
  -> South (Time: 6 min, Risk: 2, Energy Drain: 5 units)
Location: North
  -> East (Time: 3 min, Risk: 1, Energy Drain: 2 units)
  -> School (Time: 2 min, Risk: 1, Energy Drain: 1 units)
Location: East
  -> Hospital (Time: 5 min, Risk: 3, Energy Drain: 4 units)
  -> Center (Time: 2 min, Risk: 2, Energy Drain: 2 units)
Location: South
  -> West (Time: 2 min, Risk: 1, Energy Drain: 2 units)
  -> Center (Time: 4 min, Risk: 3, Energy Drain: 3 units)
Location: West
  -> Depot (Time: 4 min, Risk: 2, Energy Drain: 3 units)
Location: Hospital (Charging Station) (Critical Zone)
  -> Base (Time: 7 min, Risk: 4, Energy Drain: 6 units)
Location: Depot (Charging Station)
  -> Hospital (Time: 3 min, Risk: 2, Energy Drain: 2 units)
Location: School (Charging Station)
  -> Depot (Time: 6 min, Risk: 3, Energy Drain: 5 units)
Location: Center (Critical Zone)
  -> Hospital (Time: 2 min, Risk: 1, Energy Drain: 1 units)

Most exposed area(s):
Hospital with 3 incoming roads

The network is valid when the road directions are ignored.

Blocked area(s):
No blocked areas found.

Robot 1:
Initial position: Base
Autonomy: 8
Maximum accepted risk: 2
Optimal direct path to a critical zone: 
Base -> North -> East -> Center
Total travel time: 9
Energy consumed 7
Critical zone reached: Center

Robot 2:
Initial position: South
Autonomy: 6
Maximum accepted risk: 1
No valid direct path to a critical zone.
No valid solution even with recharge. 

Robot 3:
Initial position: West
Autonomy: 4
Maximum accepted risk: 2
No valid direct path to a critical zone.
Optimal ath with recharge: 
Chosen chargingstation: Depot
Critical zone reached after recharge: Hospital
```

## Exercise 2 - The Royal Chronicle of POLITEHNICA

### Summary

This exercise implements a record system called the "Registry of Knights" to manage a kingdom's warriors. The system tracks each knight's name, noble house, bravery score, and won battles. It allows the kingdom to rank knights, search for records within specific bravery ranges, track family houses, and find common ancestors in the hierarchy.


### Data Structure Used

***Binary Search Tree*** - Chosen because organizing knights by their unique bravery scores into a tree structure allows for very fast inserting, deleting, and searching. It also lets us easily print out sorted tournament rankings or look up common roots between data nodes.

### Features

- Inserts multiple new knights at once while automatically blocking duplicate names or duplicate bravery scores
- Removes a knight cleanly from the registry by looking up their unique name
- Prints a Tournament Ranking using In-order traversal (sorting knights from lowest to highest bravery)
- Prints a Royal Proclamation Order using Pre-order traversal
- Prints a Tribute Collection Order using Post-order traversal
- Searches for and lists all knights belonging to a specific noble House
- Searches for and filters knights whose bravery scores fall within a specific range
- Instantly finds the ***New Recruit*** (the knight with the lowest bravery) and the ***Champion of the Realm*** (the knight with the highest bravery)
- Finds the k-th valored knight based on their bravery ranking position
- Finds the Lowest Common Ancestor to discover the closest shared supervisor or root node between two different knights
- Prints archive information including total tree height, leaf nodes, and whether the records are balanced

### Implementation Details

- Built using clean custom structures (***Knight***) managing manual heap allocation safely with copy constructors and assignment operator overloads to prevent memory leaks
- Uses a stream-driven UI interface (RegistryOfKnightsUI) to read values directly from standard inputs and handle error tracking seamlessly

### Example

INPUT

```
5   //Number of knights to insert
Arthur 50 Pendragon 12
Galahad 30 Pure 8
Lancelot 70 Lake 15
Gawain 20 Orkney 5
Percival 40 Quest 6
In-order   // Print tournament ranking
House Pure   // Search all knights in House Pure
Range 25 55    // Search bravery scores between 25 and 55
Champion   // Find the highest bravery knight
Kth 2   // Find the 2nd valored knight
LCA Gawain Percival   // Find Lowest Common Ancestor for these two
Remove Percival   // Delete Percival from records
Info   //Display final archive statistics

```
OUTPUT
```
Successfully inserted 5 knights!

In-order (Tournament Ranking):
Gawain(20)
Galahad(30)
Percival(40)
Arthur(50)
Lancelot(70)

Knights of House Pure:
Galahad | bravery: 30 | 8 battles won

Knights in range 25 to 55:
Galahad | bravery: 30
Percival | bravery: 40
Arthur | bravery: 50

Champion of the Realm:
Lancelot | bravery: 70 | House Lake | 15 battles

2th valored knight: Galahad | bravery: 30 | House Pure | 8 battles

LCA of Gawain and Percival:
Galahad | bravery: 30

Successfully removed Percival!

Height of the Archive: 3
Leaf nodes (knights without children):
Gawain(20)
The archive is balanced.

```

## How to Compile and Run

- A C++ compiler is necessary
- CMake of version 3.14 or higher

### Instructions

To make sure the project compiles and runs perfectly on any machine, follow these steps inside your terminal while inside the main project folder (where this README file is located):

`cmake --build build --target run_ex1`

This will run the city map simulation. It automatically reads a list of locations, sets up charging points and danger zones, prints the full city infrastructure map, and calculates path routes for emergency robots.

Or:

`cmake --build build --target run_ex2`

This will run the tournament registry. It sets up an interactive menu system that listens to live console keywords (like In-order, Champion, LCA, or Remove) so you can search, modify, and manage knights inside the binary tree in real-time.

## Notes

- Each exrcise uses one specific data structure and a custom data structure implementation
- All cases were unit tested for both exercises for complete functionality
- The code uses clases and separate header files for an organized structure
- The exercises demonstrate the understanding and use of advanced non-linear data structures like graphs and trees





