#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include <vector>

class Building {
    public:
        Building(const std::string& name);

        const std::string& GetName() const;
    private:
        std::string name;
};

#endif // BUILDING_H
