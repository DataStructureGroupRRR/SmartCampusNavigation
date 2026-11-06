#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>
#include <vector>
#include <fstream>

#include "Building.h"

class Connections {
    public:
        void ReadConnections(std::ifstream& file, std::vector<Building> buildings);

        void TryAddConnection(const std::string& buildA, const std::string& buildB);

        bool AreConnected(const std::string& buildA, const std::string& buildB) const;
    private:
        std::vector<std::string[2]> connections;
};

#endif // CONNECTION_H
