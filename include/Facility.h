#ifndef FACILITY_H
#define FACILITY_H

#include <string>

class Facility {
    public:
        Facility(
            const std::string& id, 
            const std::string& name, 
            const std::string& building, 
            const std::string& category
        );

        const std::string& GetId() const;
        const std::string& GetName() const;
        const std::string& GetBuildingName() const;
        const std::string& GetCategory() const;
    private:
        std::string id;
        std::string name;
        std::string building;
        std::string category;
};

#endif // FACILITY_H
