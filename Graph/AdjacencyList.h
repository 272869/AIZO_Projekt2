#ifndef AIZO_P2_ADJACENCYLIST_H
#define AIZO_P2_ADJACENCYLIST_H


class AdjacencyList {
public:
    struct Edge {
        unsigned int dest; //koncowy wierzcholek
        int weight; //waga
        Edge(unsigned int dest, int weight) : dest(dest), weight(weight) {};
    };
    struct EdgeList {
        int size = 0;
        Edge *list = nullptr; //tablica wskaznikow na krawedzie
    };
private:
    int vertices;
    EdgeList *adjList;
public:
    explicit AdjacencyList(int vertices);
    ~AdjacencyList();
    void addEdge(unsigned int startVertex,unsigned int endVertex, int weight);

    int getVertices() const;
    EdgeList *getAdjList() const;

    void print();
};


#endif //AIZO_P2_ADJACENCYLIST_H
