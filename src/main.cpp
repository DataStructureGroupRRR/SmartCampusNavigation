#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int compareStrings(const string& s1, const string& s2) {
    int s1L = s1.length();
    int s2L = s2.length();

    int len = min(s1L, s2L);
    
    for (int i = 0; i < len; ++i) {
        if (s1.at(i) < s2.at(i)) {
            return -1;
        } else if (s1.at(i) > s2.at(i)) {
            return 1;
        }
    }

    if (s1L < s2L) {
        return -1;
    } else if (s1L > s2L) {
        return 1;
    } else {
        return 0;
    }
}

// TODO: Rodrigo add sorting algorithm
int findPlaceBuilding(const vector<string>& buildings, const string& name) {
    int i = 0;
    int compare = 0;
    for (; i < buildings.size(); ++i) {
        compare = compareStrings(name, buildings.at(i));
        if (compare == 0) {
            return -1;
        } else if (compare < 0) {
            break;
        }
    }

    return i;
}

void readBuildings(ifstream& file, vector<string>& buildings) {
    string name;
    int placeIdx = 0;
    while (getline(file, name)) {
        if (name.front() == '#' || (placeIdx = findPlaceBuilding(buildings, name)) == -1) {
            continue;
        }
        buildings.insert(buildings.begin() + placeIdx, name);
    }
}

int main() {
    ifstream bFile("data/buildings.txt");
    vector<string> buildings;

    if (!bFile.is_open()) {
        cout << "Could not read contents of data/buildings.txt!" << endl;
        return 1;
    }
    
    readBuildings(bFile, buildings);
    bFile.close();

    return 0;
}
