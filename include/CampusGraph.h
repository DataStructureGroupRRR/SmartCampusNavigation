// CampusGraph.h
// Undirected, unweighted campus graph stored as an adjacent list, with file loading, display, statistics, and BFS


#ifndef CAMPUS_GRAPH_H
#define CAMPUS_GRAPH_H

#include <string>
#include <vector>

// One entry of a BFS result: a building and its distance(in connections) form the start
struct BFSResultEntry {
    std::string building;
    int distance;
};

// Counts reported by a file load
struct LoadCounts {
    int accepted;
    int rejected;
};

class CampusGraph {
    public:
        CampusGraph();

        // Loads buildings from a file, returning counts of accepted and rejected lines
        LoadCounts LoadFromFile(const std::string& dir);

        // Loads connections from a file, returning counts of accepted and rejected lines
        LoadCounts LoadConnections(const std::string& dir);

        // Adds a building to the graph, returning true if successful, false if the building already exists. If false, reason is set to an error message
        bool AddBuilding(const std::string& building, std::string& reason);

        // Adds a connection between two buildings, returning true if successful, false if either building does not exist or the connection already exists. If false, reason is set to an error message
        bool AddConnection(const std::string& building1, const std::string& building2, std::string& reason);

        // Index of a  building in the graph, or -1 if not found
        int FindBuilding(const std::string& building) const;

        // Spelling stored from building.txt, or "" if unknown
        std::string CanonicalName(const std::string& building) const;


        int BuildingCount() const;
        int ConnectionCount() const;
        int Degree(int index) const;
        const std::string& BuildingName(int index) const;
        const std::vector<int>& Connections(int index) const;

        // Prints each bulding and its neighbours in insertion order
        void Display() const;

        // prints total buildings, total connections, and each building's degree in insertion order
        void DisplayCountsAndDegrees() const;

        // BFS from startIndex, fills visits in visit order with distance
        void Bfs(int startIndex, std::vector<BFSResultEntry>& results) const;

        // Runs BFS for a typed building name, printing each reachable building and its distance in insertion order. If the building is not found, prints an error message
        void DisplayReachable(const std:: string& startName)const;

        private:
            std::vector<std::string> buildings;
            std::vector<std::vector<int>> connections;
            int connectionCount;

};

#endif // CAMPUS_GRAPH_H