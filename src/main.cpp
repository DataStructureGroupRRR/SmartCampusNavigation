#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>  

#include "Building.h"
#include "Facility.h"
#include "StringUtil.h"
#include "CampusGraph.h"           
#include "DepartmentTree.h"   
#include "DepartmentMenu.h"   


using namespace std;
using namespace scn;

// TODO: Rodrigo add sorting algorithm
int findPlaceBuilding(const vector<Building>& buildings, const string& name) {
    int i = 0;
    int compare = 0;
    for (; i < buildings.size(); ++i) {
        compare = CompareStrings(name, buildings.at(i).GetName());
        if (compare == 0) {
            return -1;
        } else if (compare < 0) {
            break;
        }
    }

    return i;
}

void readBuildings(ifstream& file, vector<Building>& buildings) {
    string name;
    int placeIdx = 0;
    while (getline(file, name)) {
        if (name.front() == '#' || (placeIdx = findPlaceBuilding(buildings, name)) == -1) {
            continue;
        }
        buildings.insert(buildings.begin() + placeIdx, Building(name));
    }
}

void readFacilities(ifstream& file, const vector<Building>& buildings, vector<Facility>& facilities) {
    string id;
    string name;
    string build;
    string cat;

    while (getline(file, id, '|') && getline(file, name, '|') && getline(file, build, '|') && getline(file, cat)) {
        if (id.front() != 'F' || findPlaceBuilding(buildings, build) != -1) {
            continue;
        }

        facilities.push_back(Facility(id, name, build, cat));
    }
}

int main(int argc, char* argv[]) {
    const string dataDir = argc > 1 ? argv[1] : "data";
    int choice = 0;
    CampusGraph graph;

    LoadCounts buildingCounts = graph.LoadFromFile(dataDir);
    cout << "buildings.txt: " << buildingCounts.accepted << " accepted, "
         << buildingCounts.rejected << " rejected" << endl;

    LoadCounts connectionCounts = graph.LoadConnections(dataDir);
    cout << "connections.txt: " << connectionCounts.accepted << " accepted, "
         << connectionCounts.rejected << " rejected" << endl;

    // Share the graph's accepted building names with the facility loader.
    // Its existing lookup helper expects this separate vector to be sorted.
    vector<Building> buildings;
    for (int i = 0; i < graph.BuildingCount(); ++i) {
        const string& name = graph.BuildingName(i);
        int position = findPlaceBuilding(buildings, name);
        buildings.insert(buildings.begin() + position, Building(name));
    }

    vector<Facility> facilities;
    ifstream fFile(dataDir + "/facilities.txt");
    if (!fFile.is_open()) {
        cerr << "Error: Could not open file " << dataDir << "/facilities.txt" << endl;
    } else {
        readFacilities(fFile, buildings, facilities);
    }

    // Member C: load departments.txt (4th file, after facilities); it prints its own warnings and summary.
    DepartmentTree departments;
    departments.LoadFromFile(dataDir);

    // Prints the menu and handles user input until the user chooses to exit
    while (choice != 18) {
        cout << "1.\tView all facilities\n";
        cout << "2.\tSearch facility by ID\n";
        cout << "3.\tSearch facility by name\n";
        cout << "4.\tSearch facility by category\n";
        cout << "5.\tView campus graph\n";
        cout << "6.\tDisplay graph counts and degrees\n";
        cout << "7.\tFind reachable buildings (BFS)\n";
        cout << "8.\tFind shortest path (BFS)\n";
        cout << "9.\tAdd department\n";
        cout << "10.\tSearch department\n";
        cout << "11.\tDisplay department hierarchy\n";
        cout << "12.\tPreorder traversal\n";
        cout << "13.\tPostorder traversal\n";
        cout << "14.\tLevel-order traversal\n";
        cout << "15.\tDepartment statistics\n";
        cout << "16.\tFacility category report\n";
        cout << "17.\tGraph connectivity report\n";
        cout << "18.\tExit\n\n" << flush;

        cout << "Select an action: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1: {
                break;
            }
            case 2: {
                break;
            }
            case 3: {
                graph.Display();
                break;
            }
            case 4: {
                graph.DisplayCountsAndDegrees();
                break;
            }
            case 5: {
                string start;
                cout << "Enter starting building: ";
                if (getline(cin >> ws, start)) {
                    graph.DisplayReachable(start);
                }
                break;
            }

            case 6: {
                // Add department
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // drop the Enter left by "cin >> choice"
                HandleAddDepartment(departments);
                break;
            }
            case 7: {
                // Search department
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                HandleSearchDepartment(departments);
                break;
            }
            case 8: {
                // Display department hierarchy
                HandleDisplayHierarchy(departments);
                break;
            }
            case 9: {
                // Preorder traversal
                HandlePreorderTraversal(departments);
                break;
            }
            case 10: {
                break;
            }
            case 11: {
                break;
            }
            case 12: {
                break;
            }
            case 13: {
                break;
            }
            case 14: {
                break;
            }
            case 15: {
                break;
            }
            case 16: {
                break;
            }
            case 17: {
                break;
            }
            case 18: {
                cout << "Thank you for using our navigation service! Goodbye." << endl;
                break;
            }
            default:
                cout << "Please enter a number between 1 and 18.\n\n" << flush;
                break;
        }
    }

    return 0;
}
