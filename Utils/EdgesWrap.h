#ifndef AIZO_P2_EDGESWRAP_H
#define AIZO_P2_EDGESWRAP_H


#include <iostream>
#include <fstream>
#include <sstream>

class EdgesWrap {
public:
    struct Edge {
        int start;
        int end;
        int weight;

        Edge(){
            start = 0;
            end = 0;
            weight = 0;
        };
        Edge(int start, int end, int weight) : start(start), end(end), weight(weight) {};
    };

    Edge* edges;
    unsigned int vertices;
    unsigned int edgesCount;
    EdgesWrap(unsigned int vertices, unsigned int edgesCount, Edge* edges)
        : vertices(vertices), edgesCount(edgesCount), edges(edges){};

    virtual ~EdgesWrap() {
        delete[] edges;
    }
    void addEdge(Edge edge){
        if(edgesCount == 0){
            edges = new Edge[1]{edge};
            edgesCount++;
        } else {
            size_t newSize = sizeof(Edge) * (edgesCount + 1);
            Edge* temp = static_cast<Edge*>(std::realloc(edges, newSize));
            if (temp == nullptr) {
                std::cerr << "Failed to reallocate memory for adjacency list." << std::endl;
                return;
            }
            edges = temp;
            edges[edgesCount++] = edge;
        }
    }

    void print(){
        for(int i = 0; i < edgesCount; i++){
            std::cout << edges[i].start << " " << edges[i].end << " "<< edges[i].weight << "\n";
        }
    }


};


#endif //AIZO_P2_EDGESWRAP_H
