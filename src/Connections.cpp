#include <iostream>

#include "Connections.h"
#include "StringUtil.h"

using namespace std;
using namespace scn;

void Connections::ReadConnections(ifstream& file, vector<Building> buildings) {
    string buildA;
    string buildB;

    bool hasBuildA = false;
    bool hasBuildB = false;

    while (getline(file, buildA, '|') && getline(file, buildB)) {
        hasBuildA = false;
        hasBuildB = false;
        
        if (buildA.front() == '#') {
            continue;
        }

        for (const Building& build : buildings) {
            if (!hasBuildA && buildA == build.GetName()) {
                hasBuildA = true;
            }

            if (!hasBuildB && buildB == build.GetName()) {
                hasBuildB = true;
            }

            if (hasBuildA && hasBuildB) {
                TryAddConnection(buildA, buildB);
                break;
            }
        }

        if (!hasBuildA || !hasBuildB) {
            cout << buildA << " <---> " << buildB << " ignored: invalid building." << endl;
        }
    }
}

void Connections::TryAddConnection(const string& buildA, const string& buildB) {
    if (AreConnected(buildA, buildB)) {
        return;
    }
    
    connections.push_back({buildA, buildB});
}

bool Connections::AreConnected(const string& buildA, const string& buildB) const {
    for (int i = 0; i < connections.size(); ++i) {
        if (connections.at(i)[0] == buildA && connections.at(i)[1] == buildB) {
            return true;
        }
    }

    return false;
}
