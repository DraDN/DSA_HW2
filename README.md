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
3 2                      // number of locations, number of routes
Hospital School Depot    // all location names on ONE line separated by spaces
Hospital School 10 2 5   // route 1: from  to  time  risk  energy
School Depot 8 1 3       // route 2: from  to  time  risk  energy
1                        // number of charging stations
Hospital                 // charging station names on ONE line
1                        // number of critical zones
Depot                    // critical zone names on ONE line
2                        // number of robots
Hospital 20 3            // robot 1: start  autonomy  maxRisk
School 15 2              // robot 2: start  autonomy  maxRisk
Hospital                 // base location for unreachable areas check
```

OUTPUT
```
Location: Hospital (Charging Station)
  -> School (Time: 10 min, Risk: 2, Energy Drain: 5 units)
Location: School
  -> Depot (Time: 8 min, Risk: 1, Energy Drain: 3 units)
Location: Depot (Critical Zone)
No outgoing roads.

Most exposed area(s):
School with 1 incoming roads
Depot with 1 incoming roads

The network is valid when the road directions are ignored.

Blocked area(s):
Depot

Robot 1:
Initial position: Hospital
Autonomy: 20
Maximum accepted risk: 3
Optimal direct path to a critical zone: 
Hospital -> School -> Depot
Total travel time: 18
Energy consumed 8
Critical zone reached: Depot

Robot 2:
Initial position: School
Autonomy: 15
Maximum accepted risk: 2
Optimal direct path to a critical zone: 
School -> Depot
Total travel time: 8
Energy consumed 3
Critical zone reached: Depot

Enter base location name: 
From base Hospital, the following areas are unreachable: All areas are reachable from the base location.

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
- Uses a generic interface (RegistryOfKnightsUI), used for seamless integration of the library in applications
- A test is provided that reads from the `./EX2/test.in` file and runs through each feature, displaying the output in the console

### Example

INPUT (`test.in`)

```
10 // Number of knights ot insert
Arthur 50 Pendragon 30
Lancelot 30 Lionel 45
Gawain 70 Pendragon 22
Percival 20 Fisher 15
Tristan 40 Cornwall 28
Galahad 60 Lionel 38
Bedivere 80 Pendragon 19
Bors 25 Lionel 12
Gareth 55 Pendragon 17
Lamorak 35 Cornwall 33
// automatically prints in-order, pre-order and post-order
Pendragon // Search all knights in house Pendragon
// automatically display the knight with lowest and highest bravery score
// automatically display registry info (height, leafs and if it's balanced)
25 60 // Search for knights with bravery scores between 25 adn 60
3 // Find the 3rd most valored knight
Bors Lamorak // Find the Lowest Common Ancestor of Bors and Lamorak
Tristan // Delete Tristan from the records

```
OUTPUT
```
=== 1 ===
Successfully inserted 10 knights!

Registry after insertion (in-order):
Percival | bravery: 20 | House Fisher | 15 battles
Bors | bravery: 25 | House Lionel | 12 battles
Lancelot | bravery: 30 | House Lionel | 45 battles
Lamorak | bravery: 35 | House Cornwall | 33 battles
Tristan | bravery: 40 | House Cornwall | 28 battles
Arthur | bravery: 50 | House Pendragon | 30 battles
Gareth | bravery: 55 | House Pendragon | 17 battles
Galahad | bravery: 60 | House Lionel | 38 battles
Gawain | bravery: 70 | House Pendragon | 22 battles
Bedivere | bravery: 80 | House Pendragon | 19 battles

=== 2 ===
In-order (Tournament Ranking):
Percival(20)
Bors(25)
Lancelot(30)
Lamorak(35)
Tristan(40)
Arthur(50)
Gareth(55)
Galahad(60)
Gawain(70)
Bedivere(80)

Pre-order (Royal Proclamation):
Arthur(30)
Lancelot(45)
Percival(15)
Bors(12)
Tristan(28)
Lamorak(33)
Gawain(22)
Galahad(38)
Gareth(17)
Bedivere(19)

Post-order (Tribute Collection):
Bors(12)
Percival(15)
Lamorak(33)
Tristan(28)
Lancelot(45)
Gareth(17)
Galahad(38)
Bedivere(19)
Gawain(22)
Arthur(30)


=== 3 ===
Knights from house Pendragon:
Arthur | bravery: 50 | battles won: 30
Gareth | bravery: 55 | battles won: 17
Gawain | bravery: 70 | battles won: 22
Bedivere | bravery: 80 | battles won: 19

Newest Recruit (lowest bravery): Percival | bravery: 20 | Fisher | 15 battles

Champion of the Realm (highest bravery): Bedivere | bravery: 80 | Pendragon | 19 battles

=== 4 ===
Height of the Archive: 4
Leaf nodes (knights with no subordinates): 4
Bors (25), Lamorak (35), Gareth (55), Bedivere (80), 
The Archive is balanced.

=== 5 ===
Knights with bravery in [25, 60]:

Bors (25) | House Lionel | 12 battles
Lancelot (30) | House Lionel | 45 battles
Lamorak (35) | House Cornwall | 33 battles
Tristan (40) | House Cornwall | 28 battles
Arthur (50) | House Pendragon | 30 battles
Gareth (55) | House Pendragon | 17 battles
Galahad (60) | House Lionel | 38 battles

Total battles won by knights in range: 203

=== 6 ===
3th valored knight: Galahad | bravery: 60 | House Lionel | 38 battles

LCA of Bors and Lamorak:
Lancelot | bravery: 30

=== 7 ===
Tristan (bravery: 40) has been banished from the Registry.

Registry after banishment:
Percival(20)
Bors(25)
Lancelot(30)
Lamorak(35)
Arthur(50)
Gareth(55)
Galahad(60)
Gawain(70)
Bedivere(80)
```

## How to Compile and Run

- A C++ compiler is necessary
- CMake of version 3.14 or higher

### Instructions

#### Exercise 1

To compile and run the simulation, run the following command:

`cmake --build build --target run_ex1`

This will run the city map simulation. It automatically reads a list of locations, sets up charging points and danger zones, prints the full city infrastructure map, and calculates path routes for emergency robots.

#### Exercise 2

Run the command:

`cmake --build build --target run_test_ex2`

This will build the library and run a comprehensive test of all of the features.

## Notes

- Each exrcise uses one specific data structure and a custom data structure implementation
- All cases were unit tested for both exercises for complete functionality
- The code uses clases and separate header files for an organized structure
- The exercises demonstrate the understanding and use of advanced non-linear data structures like graphs and trees





