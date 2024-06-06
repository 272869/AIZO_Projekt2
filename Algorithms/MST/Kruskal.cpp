#include "Kruskal.h"

/*EdgesWrap Kruskal::getMST(IncidenceMatrix *matrix) {
    int edges = (int)matrix->getNumEdges();
    int vertices = (int)matrix->getNumVertices();
    auto* mstVertex = new MSTVertex[vertices];
    for(int i = 0; i < vertices; i++){ //Tworzenie dynamicznej tablicy wierzchołków MST oraz inicjalizacja ich kolorów.
        mstVertex[i].color = i;
    }
    auto* returnEdges = new EdgesWrap::Edge[vertices-1];
    int previousEdgeWeight;
    int edgeCounter = 0;
    while(edgeCounter < vertices - 1) {
        auto* toCheckList = new EdgesWrap(vertices, 0, new EdgesWrap::Edge[0]);
        int minimumWeight;
        for (int i = 0; i < edges; i++) { //przejście przez macierz w  celu indentyfikacji krawędzi i wag
            int startEdge, endEdge, weight;
            for (int j = 0; j < vertices; j++) {
                if (matrix->getMatrix()[j][i] != 0) {
                    if (matrix->getMatrix()[j][i] == -1) {
                        endEdge = j;
                    } else {
                        startEdge = j;
                        weight = matrix->getMatrix()[j][i];
                    }
                    if (startEdge != -1 && endEdge != -1) break;
                }
            }
            if ((weight < minimumWeight || minimumWeight == -1)&& (weight > previousEdgeWeight || previousEdgeWeight == -1)) {
                minimumWeight = weight;                                                                         //Aktualizacja minimumWeight
                toCheckList = new EdgesWrap(vertices, 0, new EdgesWrap::Edge[0]);       // tworzenie nowej listy krawędzi, jeśli znaleziono nową minimalną wagę
            }
            if(weight == minimumWeight){
                toCheckList->addEdge(EdgesWrap::Edge(startEdge, endEdge, weight));  //dodawanie krawędzi o tej samej minimalnej wadze do listy toCheckList.
            }
        }
        previousEdgeWeight = minimumWeight;             //Aktualizacja poprzedniej minimalnej wagi,
        for(int j = 0; j < toCheckList->edgesCount; j++){   //iteracja przez listę krawędzi toCheckList dodawanie krawędzi do MST,
            int minStart = (int)toCheckList->edges[j].start;    //jeśli łączy różne zbiory, i aktualizacja kolorów wierzchołków.
            int minEnd = (int)toCheckList->edges[j].end;
            int toColor = mstVertex[minStart].color;
            int fromColor = mstVertex[minEnd].color;
            if(toColor != fromColor){
                returnEdges[edgeCounter].weight = minimumWeight;
                returnEdges[edgeCounter].start = minStart;
                returnEdges[edgeCounter].end = minEnd;
                for(int i = 0; i < vertices; i++){
                    if(mstVertex[i].color == fromColor) mstVertex[i].color = toColor;
                }
                edgeCounter++;
            }
        }
    }

    delete[] mstVertex; //Usunięcie dynamicznej tablicy mstVertex
    return {(unsigned int)vertices, (unsigned int)vertices-1, returnEdges}; //zwrócenie obiektu EdgesWrap, zawierającego MST.
}

EdgesWrap Kruskal::getMST(AdjacencyList *list) {
    int vertices = (int)list->getVertices();
    auto* mstVertex = new MSTVertex[vertices];
    for(int i = 0; i < vertices; i++) mstVertex[i].color = i;
    auto* returnEdges = new EdgesWrap::Edge[vertices-1];
    int previousEdgeWeight;
    int k = 0;
    while(k < vertices - 1) {
        auto *toCheckList = new EdgesWrap(vertices, 0, new EdgesWrap::Edge[0]);
        int minimumWeight;
        for(int i = 0; i < vertices; i++){      //Przechodzenie przez listę sąsiedztwa,
            for(int j = 0; j < list->getAdjList()[i].size; j++){
                int tempWeight = list->getAdjList()[i].list[j].weight;
                if(tempWeight == -1) continue;
                if ((tempWeight < minimumWeight || minimumWeight == -1)&& (tempWeight > previousEdgeWeight || previousEdgeWeight == -1)) {
                    minimumWeight = tempWeight; //znajdowanie minimalnej wagi krawędzi
                    toCheckList = new EdgesWrap(vertices, 0, new EdgesWrap::Edge[0]); //tworzenie nowej listy krawędzi
                }
                if(tempWeight == minimumWeight){ // dodawanie krawędzi o tej samej minimalnej wadze do listy toCheckList
                    toCheckList->addEdge(EdgesWrap::Edge(i, list->getAdjList()[i].list[j].dest, tempWeight));
                }
            }
        }

        previousEdgeWeight = minimumWeight; //Aktualizacja poprzedniej minimalnej wagi
        for (int j = 0; j < toCheckList->edgesCount; j++) { //iteracja przez listę krawędzi toCheckList
            int minStart = (int) toCheckList->edges[j].start;
            int minEnd = (int) toCheckList->edges[j].end;
            int toColor = mstVertex[minStart].color; //dodawanie krawędzi do MST jeśli łączy różne zbiory
            int fromColor = mstVertex[minEnd].color; //aktualizacja kolorów wierzchołków.
            if (toColor != fromColor) {
                returnEdges[k].weight = minimumWeight;
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
}*/
EdgesWrap Kruskal::getMST(IncidenceMatrix *matrix) {
    int edges = (int)matrix->getNumEdges();
    int vertices = (int)matrix->getNumVertices();

    auto* mstVertex = new MSTVertex[vertices];
    for(int i = 0; i < vertices; i++){
        mstVertex[i].color = i;
    }

    auto* returnEdges = new EdgesWrap::Edge[vertices-1];

    int old = -1;
    int k = 0;
    while(k < vertices - 1) {
        auto* toCheckList = new EdgesWrap(vertices, 0, new EdgesWrap::Edge[0]);
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
                toCheckList = new EdgesWrap(vertices, 0, new EdgesWrap::Edge[0]);
            }
            if(weight == min){
                toCheckList->addEdge(EdgesWrap::Edge(eStart, eEnd, weight));
            }
        }
        old = min;
        for(int j = 0; j < toCheckList->edgesCount; j++){
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

EdgesWrap Kruskal::getMST(AdjacencyList *list) {
    int vertices = (int)list->getVertices();

    auto* mstVertex = new MSTVertex[vertices];
    for(int i = 0; i < vertices; i++){
        mstVertex[i].color = i;
    }

    auto* returnEdges = new EdgesWrap::Edge[vertices-1];

    int old = -1;
    int k = 0;
    while(k < vertices - 1) {
        auto *toCheckList = new EdgesWrap(vertices, 0, new EdgesWrap::Edge[0]);
        int min = -1;
        for(int i = 0; i < vertices; i++){
            for(int j = 0; j < list->getAdjList()[i].size; j++){
                int tempWeight = list->getAdjList()[i].list[j].weight;
                if(tempWeight == -1) continue;
                if ((tempWeight < min || min == -1)&& (tempWeight > old || old == -1)) {
                    min = tempWeight;
                    toCheckList = new EdgesWrap(vertices, 0, new EdgesWrap::Edge[0]);
                }
                if(tempWeight == min){
                    toCheckList->addEdge(EdgesWrap::Edge(i, list->getAdjList()[i].list[j].dest, tempWeight));
                }
            }
        }

        old = min;
        for (int j = 0; j < toCheckList->edgesCount; j++) {
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
