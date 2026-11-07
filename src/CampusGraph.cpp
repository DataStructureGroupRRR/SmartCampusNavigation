// CampusGraph.cpp

// Implementation of the CampusGraph class: loading, display, statistics, and BFS 

#include "CampusGraph.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>

#include "StringUtil.h"

using namespace std;
using namespace scn;

// Constructor 
CampusGraph::CampusGraph(): connectionCount(0) {
}

// Adds a building after trimming, rejects empty name and case insensitive duplicates
bool CampusGraph::AddBuilding(const std::string& building, std::string& reason) {
    string trimmed = Trim(building);
    if (trimmed.empty()) {
        reason = "Empty building name";
        return false;
    }
    if (FindBuilding(trimmed) != -1) {
        reason = "duplicate building \"" + trimmed + "\" (matches \"" + CanonicalName(trimmed) + "\")";
        return false;
    }
    buildings.push_back(trimmed);
    connections.push_back(vector<int>());
    return true;
}

/**
Adds an undirected edge; rejects unknown buildings, self-loops, and duplicate edges. Returns true if successful, false if rejected, with reason set to an error message.
*/
bool CampusGraph::AddConnection(const std::string& building1, const std::string& building2, std::string& reason) {
    int index1 = FindBuilding(building1);
    int index2 = FindBuilding(building2);

    if (index1 == -1) {
        reason = "unknown building \"" + Trim(building1) + "\"";
        return false;
    }

    if (index2 == -1) {
        reason = "unknown building \"" + Trim(building2) + "\"";
        return false;
    }

    if (index1 == index2) {
        reason = "connection from \"" + Trim(building1) + "\" to itself";
        return false;
    }

    for (size_t i = 0; i < connections[index1].size(); ++i) {
        if (connections[index1][i] == index2) {
            reason = "duplicate connection from \"" + Trim(building1) + "\" to \"" + Trim(building2) + "\"";
            return false;
        }
    }

    adjacencyList[index1].push_back(index2);
    adjacencyList[index2].push_back(index1);
    ++connectionCount;
    return true;

}

// Loads buildings.txt from the given directory
LoadCounts CampusGraph::LoadFromFile(const std::string& dir) {
    const string filename = "buildings.txt";
    LoadCounts counts = {0, 0};

    ifstream file(dir + "/" + filename).c_str());

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << dir + "/" + filename << endl;
        return counts;
    }

    string line;
    int lineNum = 0;
    while (getline(file, line)){
        ++lineNum;
        if (IsBlankOrComment(line)) {
            continue;
        }
        
        string trimmed = Trim(line);
        string reason;

        if (trimmed.find('|') != string::npos) {
            reason = "wrong field count (expected 1 field, found 2)";
        } else if (AddBuilding(trimmed, reason)) {
            ++counts.accepted;
        } else {
            ++counts.rejected;
            cerr << "Error in " << filename << " line " << lineNum << ": " << reason << endl;
        }
        return counts;
    }

// Loads connections.txt from the given directory
LoadCounts CampusGraph::LoadConnections(const std::string& dir) {
    const string filename = "connections.txt";
    LoadCounts counts = {0, 0};

    ifstream file(dir + "/" + filename).c_str()); 

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << dir + "/" + filename << endl;
        return counts;
    }

    string line;
    int lineNum = 0;
    while (getline(file, line)){
        ++lineNum;
        if (IsBlankOrComment(line)) {
            continue;
        }
        
        vector<string> fields = SplitFields(line, '|');
        string reason;

        if (fields.size() != 2) {
            reason = "wrong field count (expected 2 fields, found " + to_string(fields.size()) + ")";
        } else if (AddConnection(fields[0], fields[1], reason)) {
            ++counts.accepted;
        } else {
            ++counts.rejected;
            cerr << "Error in " << filename << " line " << lineNum << ": " << reason << endl;
        }
    }
    return counts;
}


// Case-insensitive search for a building, returning its index or -1 if not found
int CampusGraph::FindBuilding(const std::string& building) const { 
    string trimmed = Trim(building);
    for (size_t i = 0; i < buildings.size(); ++i) {
        if (EqualsIgnoreCase(trimmed, buildings[i])) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// returns the building spellings from buildings.txt, or "" if not found
string CampusGraph::CanonicalName(const std::string& building) const {
    int index = FindBuilding(building);
    return index == -1 ? "" : buildings[index];
}

int campusGraph::BuildingCount() const {
    return static_cast<int>(buildings.size());
}

int campusGraph::ConnectionCount() const {
    return connectionCount;
}

//Degree = number of distinct neighbours
int campusGraph::Degree(int index) const {
    return static_cast<int>(connections[index].size());
}

const string& campusGraph::BuildingName(int index) const {
    return buildings[index];
}

const vector<int>& campusGraph::Connections(int index) const {
    return connections[index];
}

// Prints every building with its neighbours in insertion order
void campusGraph::DisplayGraph() const{
    if (buildings.empty()) {
        cout << "No buildings in the graph." << endl;
        return;
    }

    cout << "Campus Graph:" << endl;
    for (size_t i = 0; i < buildings.size(); ++i) {
        cout << "Building: " << buildings[i] << endl;
        cout << "Connected to: ";
        if (connections[i].empty()) {
            cout << "None";
        } else {
            for (size_t j = 0; j < connections[i].size(); ++j) {
                if (j > 0) {
                    cout << ", ";
                }
                cout << buildings[connections[i][j]];
            }
        }
        cout << endl;
    }
}

// Prints total and each building's degree
void campusGraph::DisplayCountsAndDegrees() const {
    cout << "Total buildings: " << BuildingCount() << endl;
    cout << "Total connections: " << ConnectionCount() << endl;
    if (buildings.empty()) {
        cout << "No buildings in the graph." << endl;
        return;
    }

    cout << "Building degrees:" << endl;
    for (size_t i = 0; i < buildings.size(); ++i) {
        cout << buildings[i] << ": " << Degree(static_cast<int>(i)) << endl;
    }
}

// Breadth-first seach using a queue and a visited array
// A building is marked visisted when it is added to the queue
void CampusGraph::Bfs(int startIndex, vector<BfsVisit>& visits) const {
    visits.clear();
    if (startIndex < 0 || startIndex >= BuildingCount()) {
        return;
    }

    vector<bool> visited(BuildingCount(), false);
    vector<int> distance(BuildingCount(), 0);
    queue<int> q;

    visited[startIndex] = true;
    q.push(startIndex);

    while (!q.empty()) {
        int current = q.front();
        q.pop();
       
        BfsVisit v;
        v.building = buildings[current];
        v.distance = distance[current];
        visits.push_back(v);

        for (size_t i = 0; i < connections[current].size(); ++i) {
            int neighbor = connections[current][i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                distance[neighbor] = distance[current] + 1;
                q.push(neighbor);
            }
        }
    }
    
}

// Runs BFS from a typed building name and prints the results. 
void CampusGraph::DisplayReachable(const std::string& startName) const {
    int startIndex = FindBuilding(startName);
    if (startIndex == -1) {
        cout << "Error: Building \"" << Trim(startName) << "\" not found." << endl;
        return;
    }

    vector<BfsVisit> visits;
    Bfs(startIndex, visits);

    cout << "Reachable buildings from \"" << buildings[startIndex] << "\":" << endl;
    for (const auto& visit : visits) {
        cout << visit.building << " (distance: " << visit.distance << ")" << endl;
    }
}

