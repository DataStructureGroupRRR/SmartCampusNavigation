#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>
#include <vector>
#include <fstream>
#include <array>   // USed to store the endpoints of a connection

#include "Building.h"


class Connections {
    public:
        void ReadConnections(std::ifstream& file, std::vector<Building> buildings);

        void TryAddConnection(const std::string& buildA, const std::string& buildB);

        bool AreConnected(const std::string& buildA, const std::string& buildB) const;
    private:

        // Changes raw string[2] to std:;array<std::string, 2> for better type safety and clarity
        std::vector<std::array<std::string, 2>> connections;
};

#endif // CONNECTION_H
