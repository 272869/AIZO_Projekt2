#include "Prim.h"

EdgeList Prim::getMST(IncidenceMatrix *matrix) {
    int vertNum = (int)matrix->getNumVertices();
    auto* mstVertex = new MSTVertex[vertNum]; // tablica struktur MSTVertex dla każdego wierzchołka
    mstVertex[0].minWeight = 0; //Pierwszy wierzcholek ma wage 0, bo do niego nie mozna dojsc

//dodaje każdy kolejny wierzchołek do MST
    for(int k = 0; k < vertNum - 1; k++) {
        int minParentWeight = -1; //minParentWeight przechowuje najmniejszą wagę spośród wierzchołków do odwiedzenia.
        int minParent = -1; //minParent przechowuje indeks wierzchołka z najmniejszą wagą, który zostanie dodany do MST.
        // Szukaj wierzchołka o najmniejszej wadze, który nie został jeszcze odwiedzony
        for (int i = 0; i < vertNum; i++) { //Przechodzimy przez wszystkie wierzchołki.
            if (!mstVertex[i].visited && mstVertex[i].minWeight > -1 && (mstVertex[i].minWeight < minParentWeight || minParentWeight == -1)) { //i ma najmniejszą wagę minWeight
                minParentWeight = mstVertex[i].minWeight;
                minParent = i;
            }
        }
// Aktualizuj minimalne wagi dla wszystkich sąsiadujących wierzchołków
        for (int i = 0; i < matrix->getNumEdges(); i++) { //Przechodzimy przez wszystkie krawędzie w grafie.
            int tempParWeight = matrix->getMatrix()[minParent][i]; //tempParWeight to waga krawędzi łączącej minParent z krawędzią i.
            if (tempParWeight != 0) { //czy istnieje krawędź łącząca wybrany wierzchołek z innymi wierzchołkami
                for (int j = 0; j < vertNum; j++) { //Przechodzimy przez wszystkie wierzchołki j, które są różne od minParent.
                    if (minParent == j) continue; // Pomijaj samego siebie
                    int tempChildWeight = matrix->getMatrix()[j][i]; //tempChildWeight to waga krawędzi łączącej wierzchołek j z krawędzią i.
                    if (tempChildWeight != 0) {
                        if (tempChildWeight > tempParWeight) { //Uaktualniamy tempParWeight do większej z wag między tempParWeight i tempChildWeight
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
        mstVertex[minParent].visited = true; //Oznaczamy wierzchołek minParent jako odwiedzony
    }
    // Tworzenie listy krawędzi dla MST
    auto* edges = new EdgeList::Edge[vertNum-1];
    int j = 0;
    for (int i = 0; i < vertNum; i++) {
        if(mstVertex[i].parent == -1) continue; // Pomijaj wierzchołki bez rodzica (startowy)
        edges[j].start = mstVertex[i].parent;// Dodaj rodzica jako początek krawędzi
        edges[j].end = i;
        edges[j].weight = mstVertex[i].minWeight;
        j++;
    }

    delete[] mstVertex;
    return {(unsigned  int)vertNum, (unsigned  int)vertNum-1, edges};
}

EdgeList Prim::getMST(AdjacencyList *list) {
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
    auto* edges = new EdgeList::Edge[vertNum-1]; // Tablica krawędzi w MST.
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
