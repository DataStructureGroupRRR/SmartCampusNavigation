#include "Building.h"

using namespace std;

Building::Building(const string& name) : name(name) {

}

const string& Building::GetName() const {
    return name;
}
