#include "Prim.h"

EdgesWrap Prim::getMST(IncidenceMatrix *matrix) {
    int vertNum = (int)matrix->getNumVertices();
    auto* mstVertex = new MSTVertex[vertNum];
    mstVertex[0].minWeight = 0;


    for(int k = 0; k < vertNum - 1; k++) {
        int minParentWeight = -1;
        int minParent = -1;
        for (int i = 0; i < vertNum; i++) {
            if (!mstVertex[i].visited && mstVertex[i].minWeight > -1
                && (mstVertex[i].minWeight < minParentWeight || minParentWeight == -1)) {
                minParentWeight = mstVertex[i].minWeight;
                minParent = i;
            }
        }

        for (int i = 0; i < matrix->getNumEdges(); i++) {
            int tempParWeight = matrix->getMatrix()[minParent][i];
            if (tempParWeight != 0) {
                for (int j = 0; j < vertNum; j++) {
                    if (minParent == j) continue;
                    int tempChildWeight = matrix->getMatrix()[j][i];
                    if (tempChildWeight != 0) {
                        if (tempChildWeight > tempParWeight) {
                            tempParWeight = tempChildWeight;
                        }
                        if (!mstVertex[j].visited && (mstVertex[j].minWeight > tempParWeight || mstVertex[j].minWeight == -1)) {
                            mstVertex[j].minWeight = tempParWeight;
                            mstVertex[j].parent = minParent;
                        }
                    }
                }
            }
        }
        mstVertex[minParent].visited = true;
    }
    auto* edges = new EdgesWrap::Edge[vertNum-1];
    int j = 0;
    for (int i = 0; i < vertNum; i++) {
        if(mstVertex[i].parent == -1) continue;
        edges[j].start = mstVertex[i].parent;
        edges[j].end = i;
        edges[j].weight = mstVertex[i].minWeight;
        j++;
    }

    delete[] mstVertex;
    return {(unsigned  int)vertNum, (unsigned  int)vertNum-1, edges};
}
EdgesWrap Prim::getMST(AdjacencyList *list) {
    int vertNum = (int)list->getVertices();
    auto* mstVertex = new MSTVertex[vertNum];
    mstVertex[0].minWeight = 0;

    for(int k = 0; k < vertNum - 1; k++) {
        int minParentWeight = -1;
        int minParent = -1;
        for (int i = 0; i < vertNum; i++) {
            if (!mstVertex[i].visited && mstVertex[i].minWeight > -1
                && (mstVertex[i].minWeight < minParentWeight || minParentWeight == -1)) {
                minParentWeight = mstVertex[i].minWeight;
                minParent = i;
            }
        }

        AdjacencyList::EdgeList edgeList = list->getAdjList()[minParent]; // Pobranie listy sąsiedztwa dla wybranego wierzchołka.
        for(int i = 0; i < edgeList.size; i++){
            int tempWeight = edgeList.list[i].weight; // Pobranie wagi krawędzi.
            if(tempWeight == -1){ // Sprawdzenie, czy krawędź nie jest odwiedzona.
                AdjacencyList::EdgeList tempEdgeList = list->getAdjList()[edgeList.list[i].dest]; // Pobranie listy sąsiedztwa dla sąsiedniego wierzchołka.
                for(int j = 0; j < tempEdgeList.size; j++){
                    if(tempEdgeList.list[j].dest == minParent && tempEdgeList.list[j].weight != -1){
                        tempWeight = tempEdgeList.list[j].weight;
                        break;
                    }
                }
            }
            int tempDest = (int)edgeList.list[i].dest; // Pobranie sąsiedniego wierzchołka.
            if (!mstVertex[tempDest].visited && (mstVertex[tempDest].minWeight > tempWeight || mstVertex[tempDest].minWeight == -1)) {
                mstVertex[tempDest].minWeight = tempWeight; // Aktualizacja minimalnej wagi krawędzi dla wierzchołka.
                mstVertex[tempDest].parent = minParent; // Ustawienie rodzica wierzchołka.
            }
        }
        mstVertex[minParent].visited = true; // Oznaczenie wierzchołka jako odwiedzonego.
    }
    auto* edges = new EdgesWrap::Edge[vertNum-1]; // Tablica krawędzi w MST.
    int j = 0;
    for (int i = 0; i < vertNum; i++) {
        if(mstVertex[i].parent == -1) continue;
        edges[j].start = mstVertex[i].parent; // Ustawienie wierzchołka początkowego krawędzi.
        edges[j].end = i; // Ustawienie wierzchołka końcowego krawędzi.
        edges[j].weight = mstVertex[i].minWeight; // Ustawienie wagi krawędzi.
        j++;
    }

    delete[] mstVertex;
    return {(unsigned  int)vertNum, (unsigned  int)vertNum-1, edges};
}
