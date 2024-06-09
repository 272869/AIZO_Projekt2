#include "Kruskal.h"

EdgeList Kruskal::getMST(IncidenceMatrix *matrix) {
    int edges = (int)matrix->getNumEdges();
    int vertices = (int)matrix->getNumVertices();

    auto* mstVertex = new MSTVertex[vertices];
    for(int i = 0; i < vertices; i++){
        mstVertex[i].color = i;
    }

    auto* returnEdges = new EdgeList::Edge[vertices-1];

    int old = -1;
    int k = 0;
    while(k < vertices - 1) {
        auto* toCheckList = new EdgeList(vertices, 0, new EdgeList::Edge[0]);
        int min = -1;
        for (int i = 0; i < edges; i++) {
            int eStart = -1;
            int eEnd = -1;
            int weight = -1;
            for (int j = 0; j < vertices; j++) {
                if (matrix->getMatrix()[j][i] != 0) {
                    if (matrix->getMatrix()[j][i] == -1) {
                        eEnd = j;
                    } else {
                        eStart = j;
                        weight = matrix->getMatrix()[j][i];
                    }
                    if (eStart != -1 && eEnd != -1) break;
                }
            }
            if ((weight < min || min == -1)&& (weight > old || old == -1)) {
                min = weight;
                toCheckList = new EdgeList(vertices, 0, new EdgeList::Edge[0]);
            }
            if(weight == min){
                toCheckList->addEdge(EdgeList::Edge(eStart, eEnd, weight));
            }
        }
        old = min;
        for(int j = 0; j < toCheckList->edgesNum; j++){
            int minStart = (int)toCheckList->edges[j].start;
            int minEnd = (int)toCheckList->edges[j].end;
            int toColor = mstVertex[minStart].color;
            int fromColor = mstVertex[minEnd].color;
            if(toColor != fromColor){
                returnEdges[k].weight = min;
                returnEdges[k].start = minStart;
                returnEdges[k].end = minEnd;
                for(int i = 0; i < vertices; i++){
                    if(mstVertex[i].color == fromColor) mstVertex[i].color = toColor;
                }
                k++;
            }
        }
    }

    delete[] mstVertex;
    return {(unsigned int)vertices, (unsigned int)vertices-1, returnEdges};
}

EdgeList Kruskal::getMST(AdjacencyList *list) {
    int vertices = (int)list->getVertices();

    auto* mstVertex = new MSTVertex[vertices];
    for(int i = 0; i < vertices; i++){
        mstVertex[i].color = i;
    }

    auto* returnEdges = new EdgeList::Edge[vertices-1];

    int old = -1;
    int k = 0;
    while(k < vertices - 1) {
        auto *toCheckList = new EdgeList(vertices, 0, new EdgeList::Edge[0]);
        int min = -1;
        for(int i = 0; i < vertices; i++){
            for(int j = 0; j < list->getAdjList()[i].size; j++){
                int tempWeight = list->getAdjList()[i].list[j].weight;
                if(tempWeight == -1) continue;
                if ((tempWeight < min || min == -1)&& (tempWeight > old || old == -1)) {
                    min = tempWeight;
                    toCheckList = new EdgeList(vertices, 0, new EdgeList::Edge[0]);
                }
                if(tempWeight == min){
                    toCheckList->addEdge(EdgeList::Edge(i, list->getAdjList()[i].list[j].dest, tempWeight));
                }
            }
        }

        old = min;
        for (int j = 0; j < toCheckList->edgesNum; j++) {
            int minStart = (int) toCheckList->edges[j].start;
            int minEnd = (int) toCheckList->edges[j].end;
            int toColor = mstVertex[minStart].color;
            int fromColor = mstVertex[minEnd].color;
            if (toColor != fromColor) {
                returnEdges[k].weight = min;
                returnEdges[k].start = minStart;
                returnEdges[k].end = minEnd;
                for (int i = 0; i < vertices; i++) {
                    if (mstVertex[i].color == fromColor) mstVertex[i].color = toColor;
                }
                k++;
            }
        }
    }
    delete[] mstVertex;
    return {(unsigned int)vertices, (unsigned int)vertices-1, returnEdges};
}
