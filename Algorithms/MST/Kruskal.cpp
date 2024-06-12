#include <algorithm>
#include "Kruskal.h"

EdgeList Kruskal::getMST(IncidenceMatrix *matrix) {
    int edges = (int)matrix->getNumEdges();
    int vertices = (int)matrix->getNumVertices();
//    Tworzy się tablica mstVertex, gdzie każdy wierzchołek jest inicjalizowany
//    ze swoim kolorem równym jego indeksowi. Kolory są używane do śledzenia,
//    które wierzchołki należą do tego samego drzewa.
    auto* mstVertex = new MSTVertex[vertices];
    for(int i = 0; i < vertices; i++){
        mstVertex[i].color = i;
    }
//    Tworzona jest tablica returnEdges, która będzie przechowywać krawędzie minimalnego drzewa rozpinającego.
    auto* returnEdges = new EdgeList::Edge[vertices-1];

    int previousWeight = -1;
    int k = 0;
    //pętla, w której dodaje krawędzie do MST, aż osiągnie liczbę V−1 krawędzi.
    while(k < vertices - 1) {
        auto* toCheckList = new EdgeList(vertices, 0, new EdgeList::Edge[0]);
        int min = -1; //min to minimalna waga krawędzi znaleziona w bieżącej iteracji.
        //przechodzimy przez krawędzie
        for (int i = 0; i < edges; i++) {
            int eStart = -1;
            int eEnd = -1;
            int weight = -1;
            //znajdujemy krawedz w macierzy
            for (int j = 0; j < vertices; j++) {
                if (matrix->getMatrix()[j][i] != 0) { //sprawdzamy czy istnieje krawędz
                    if (matrix->getMatrix()[j][i] == -1) { //sprawdzamy czy to koniec krawędzi
                        eEnd = j;
                    } else { //jesli nie to znaczy ze to koniec krawędzi a wartosc komorki to jej waga
                        eStart = j;
                        weight = matrix->getMatrix()[j][i];
                    }
                    if (eStart != -1 && eEnd != -1) break; //jesli krawedz znaleziona przerywamy petle
                }
            }
            //Sprawdza, czy bieżąca waga krawędzi (weight) jest mniejsza od aktualnie znalezionej minimalnej wagi (min).
            //min == -1 jest warunkiem początkowym, który zapewnia, że pierwszy napotkany weight zostanie uznany za min.
            //Sprawdza, czy bieżąca waga krawędzi (weight) jest większa niż previousWeight, czyli waga krawędzi z poprzedniej iteracji.
            //previousWeight == -1 jest warunkiem początkowym, który pozwala na zaakceptowanie każdej wagi w pierwszej iteracji.
            //Jeżeli oba warunki są spełnione (czyli bieżąca krawędź ma wagę większą niż poprzednio przetwarzana krawędź,
            //ale mniejszą niż dotychczas znalezione minimalne wartości), min jest aktualizowane na bieżącą wartość weight,
            // a toCheckList jest inicjalizowana jako nowa, pusta lista krawędzi.
            if ((weight < min || min == -1)&& (weight > previousWeight || previousWeight == -1)) {
                min = weight;
                toCheckList = new EdgeList(vertices, 0, new EdgeList::Edge[0]);
            }
            //Sprawdza, czy waga bieżącej krawędzi (weight) jest równa aktualnie najmniejszej znalezionej wadze (min).
            //Jeżeli bieżąca krawędź ma wagę równą min, jest dodawana do listy toCheckList.
            //Warunek ten zapewnia, że wszystkie krawędzie o aktualnie najmniejszej wadze zostaną zebrane w toCheckList
            if(weight == min){
                toCheckList->addEdge(EdgeList::Edge(eStart, eEnd, weight));
            }
        }
        previousWeight = min; // aktualizujemy poprzednią krawędź
        for(int j = 0; j < toCheckList->edgesNum; j++){
            int minStart = (int)toCheckList->edges[j].start;
            int minEnd = (int)toCheckList->edges[j].end;
            int toColor = mstVertex[minStart].color;
            int fromColor = mstVertex[minEnd].color;
            if(toColor != fromColor){ //czy krawędź łączy dwa rózne poddrzewa
                returnEdges[k].weight = min;
                returnEdges[k].start = minStart;
                returnEdges[k].end = minEnd;
                for(int i = 0; i < vertices; i++){
                    if(mstVertex[i].color == fromColor) mstVertex[i].color = toColor; //zmieniamy kolor
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

    int previousWeight = -1;
    int k = 0;
    while(k < vertices - 1) {
        auto *toCheckList = new EdgeList(vertices, 0, new EdgeList::Edge[0]);
        int min = -1;
        for(int i = 0; i < vertices; i++){
            for(int j = 0; j < list->getAdjList()[i].size; j++){
                int tempWeight = list->getAdjList()[i].list[j].weight;
                if(tempWeight == -1) continue;
                if ((tempWeight < min || min == -1)&& (tempWeight > previousWeight || previousWeight == -1)) {
                    min = tempWeight;
                    toCheckList = new EdgeList(vertices, 0, new EdgeList::Edge[0]);
                }
                if(tempWeight == min){
                    toCheckList->addEdge(EdgeList::Edge(i, list->getAdjList()[i].list[j].dest, tempWeight));
                }
            }
        }

        previousWeight = min;
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



