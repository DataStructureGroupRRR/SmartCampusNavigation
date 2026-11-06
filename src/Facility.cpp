#include "Facility.h"

using namespace std;

Facility::Facility(
    const string& id, 
    const string& name, 
    const string& building, 
    const string& category
) : id(id), name(name), building(building), category(category) {
    
}

const string& Facility::GetId() const {
    return id;
}

const string& Facility::GetName() const {
    return name;
}

const string& Facility::GetBuildingName() const {
    return building;
}

const string& Facility::GetCategory() const {
    return category;
}
