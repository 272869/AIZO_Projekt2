#ifndef AIZO_P2_EDGESWRAP_H
#define AIZO_P2_EDGESWRAP_H

#include <iostream>
#include <fstream>
#include <sstream>

class EdgeList {
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

    Edge* edges; //Wskaźnik na tablicę krawędzi, które są częścią grafu.
    unsigned int vertices;
    unsigned int edgesNum;
    EdgeList(unsigned int vertices, unsigned int edgesNum, Edge* edges)
        : vertices(vertices), edgesNum(edgesNum), edges(edges){};

    virtual ~EdgeList() {
        delete[] edges;
    }
    /* Dodaje nową krawędź do grafu. Jeśli graf jest pusty, alokuje pamięć dla jednej krawędzi,
     * w przeciwnym razie używa std::realloc do ponownej alokacji pamięci dla powiększonej tablicy krawędzi.*/
    void addEdge(Edge edge){
        if(edgesNum == 0){
            edges = new Edge[1]{edge};
            edgesNum++;
        } else {
            int newSize = sizeof(Edge) * (edgesNum + 1);
            Edge* temp = static_cast<Edge*>(std::realloc(edges, newSize));
            if (temp == nullptr) {
                std::cerr << "Failed to reallocate memory." << std::endl;
                return;
            }
            edges = temp;
            edges[edgesNum++] = edge;
        }
    }

    void print(){
        for(int i = 0; i < edgesNum; i++){
            std::cout << edges[i].start << " " << edges[i].end << " "<< edges[i].weight << "\n";
        }
    }
};

#endif //AIZO_P2_EDGESWRAP_H
