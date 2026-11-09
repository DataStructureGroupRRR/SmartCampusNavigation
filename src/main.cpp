#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

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

    // Load departments after facilities; the loader prints its summary.
    DepartmentTree departments;
    departments.LoadFromFile(dataDir);

    // Read complete lines so invalid input and blank names recover cleanly.
    while (true) {
        cout << "1.\tView all facilities\n"
             << "2.\tSearch facility by ID\n"
             << "3.\tView campus graph\n"
             << "4.\tDisplay graph counts and degrees\n"
             << "5.\tFind reachable buildings (BFS)\n"
             << "6.\tAdd department\n"
             << "7.\tSearch department\n"
             << "8.\tDisplay department hierarchy\n"
             << "9.\tRun preorder traversal\n"
             << "0.\tExit\n\n"
             << "Select an action: " << flush;

        string line;
        if (!getline(cin, line)) {
            cout << "\nInput ended. Goodbye." << endl;
            break;
        }
        istringstream input(line);
        string extra;
        if (!(input >> choice) || (input >> extra) || choice < 0 || choice > 9) {
            cout << "Error: Please enter a whole number between 0 and 9.\n\n";
            continue;
        }

        switch (choice) {
            case 0:
                cout << "Thank you for using our navigation service! Goodbye." << endl;
                return 0;
	    
case 1: {
    if (facilities.empty()) {
        cout << "No facilities available." << endl;
        break;
    }

    cout << "All Facilities:" << endl;

    for (const Facility& facility : facilities) {
        cout << "ID: " << facility.GetId() << endl;
        cout << "Name: " << facility.GetName() << endl;
        cout << "Building: " << facility.GetBuildingName() << endl;
        cout << "Category: " << facility.GetCategory() << endl;
        cout << "------------------------" << endl;
    }
    break;
}

case 2: {
    string searchId;
    cout << "Enter facility ID: ";
    if (!getline(cin, searchId)) {
        cout << "\nInput ended. Goodbye." << endl;
        return 0;
    }

    bool found = false;

    for (const Facility& facility : facilities) {
        if (facility.GetId() == searchId) {
            cout << "Facility found:" << endl;
            cout << "ID: " << facility.GetId() << endl;
            cout << "Name: " << facility.GetName() << endl;
            cout << "Building: " << facility.GetBuildingName() << endl;
            cout << "Category: " << facility.GetCategory() << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Facility not found." << endl;
    }
    break;
}

            case 3:
                graph.Display();
                break;
            case 4:
                graph.DisplayCountsAndDegrees();
                break;
            case 5: {
                string start;
                cout << "Enter starting building: " << flush;

                if (!getline(cin, start)) {
                    cout << "\nInput ended. Goodbye." << endl;
                    return 0;
                }
                graph.DisplayReachable(start);
                break;
            }
            case 6:
                HandleAddDepartment(departments);
                break;
            case 7:
                HandleSearchDepartment(departments);
                break;
            case 8:
                HandleDisplayHierarchy(departments);
                break;
            case 9:
                HandlePreorderTraversal(departments);
                break;
            default:
                // Facility owners will integrate options 1 and 2.
                cout << "This feature is awaiting module integration." << endl;
                break;
        }
    }
    return 0;
}
