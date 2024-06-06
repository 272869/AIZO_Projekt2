#ifndef AIZO_P2_INCIDENCEMATRIX_H
#define AIZO_P2_INCIDENCEMATRIX_H


class IncidenceMatrix {
private:
    int **matrix;
    unsigned int numVertices;
    unsigned int numEdges;
public:
    IncidenceMatrix(unsigned int vertices, unsigned int edges);
    ~IncidenceMatrix();
    void addEdge(unsigned int startVertex, unsigned int endVertex, unsigned short weight, unsigned int edge);

    [[nodiscard]] int **getMatrix() const;
    [[nodiscard]] unsigned int getNumVertices() const;
    [[nodiscard]] unsigned int getNumEdges() const;

    void print();

};


#endif //AIZO_P2_INCIDENCEMATRIX_H
