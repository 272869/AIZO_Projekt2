
#include <fstream>
#include <sstream>
#include "EdgesList.h"
#include "ReadGraph.h"

EdgeList ReadGraph::readGraph(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    unsigned int vertices, edgesCount;
    file >> edgesCount >> vertices;
    auto* edges = new EdgeList::Edge[edgesCount];
    for (unsigned int i = 0; i < edgesCount; ++i) {
        int start, end, weight;
        file >> start >> end >> weight;
        edges[i] = {start, end, weight};
    }
    file.close();
    return {vertices, edgesCount, edges};
}

