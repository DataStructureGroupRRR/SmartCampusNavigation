#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "Building.h"
#include "Connections.h"
#include "Facility.h"
#include "StringUtil.h"

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

int main() {
    int choice = 0;
    
    ifstream bFile("data/buildings.txt");
    if (!bFile.is_open()) {
        cout << "Could not read contents of data/buildings.txt!" << endl;
        return 1;
    }

    ifstream cFile("data/connections.txt");
    if (!cFile.is_open()) {
        cout << "Could not read contents of data/connections.txt!" << endl;
        return 1;
    }

    ifstream fFile("data/facilities.txt");
    if (!fFile.is_open()) {
        cout << "Could not read contents of data/facilities.txt!" << endl;
        return 1;
    }

    vector<Building> buildings;
    Connections connections;
    vector<Facility> facilities;
    
    readBuildings(bFile, buildings);
    bFile.close();

    connections.ReadConnections(cFile, buildings);
    cFile.close();

    readFacilities(fFile, buildings, facilities);
    fFile.close();

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
                graph.DisplayGraph();
                break;
            }
            case 4: {
                graph.DisplayCountsAndDegrees();
                break;
            }
            case 5: {
                string start;
                if (readName("Enter stating building: ", start)){
                    graph.DisplayReachableBuildings(start);
                }
                break;
            }

            case 6: {
                break;
            }
            case 7: {
                break;
            }
            case 8: {
                break;
            }
            case 9: {
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
