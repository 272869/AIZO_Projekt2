#include <iostream>
#include "Menu.h"
#include "GenerateGraph.h"
#include "TransformGenerated.h"
#include "../Algorithms/SPT/BellmanFord.h"
#include "../Algorithms/MST/Prim.h"
#include "../Algorithms/MST/Kruskal.h"
#include "../Algorithms/SPT/Dijkstra.h"
#include "ReadGraph.h"

void Menu::mainMenu() {
    while (true){
        std::cout<< "Wybierz typ :" << std::endl;
        std::cout<< "1. MST" << std::endl;
        std::cout<< "2. SPT" << std::endl;
        std::cout<< "3. Test" << std::endl;
        std::cout<< "0. Wyjdz" << std::endl;
        int mode;
        std::cin >> mode;
        switch (mode) {
            case 1:
                MstMenu();
                break;
            case 2:
                SptMenu();
                break;
            case 3:
                test.startTests();
                break;
            case 0:
                return;
            default:
                break;
        }
    }

}

void Menu::MstMenu() {
    IncidenceMatrix* matrix = nullptr;
    AdjacencyList* list = nullptr;
    while (true) {
        std::cout << "Operacje dla grafow:" << std::endl;
        std::cout << "1. Generuj graf losowo" << std::endl;
        std::cout << "2. Wczytaj graf z pliku" << std::endl;
        std::cout << "3. Wyswietl poczatkowy graf" << std::endl;
        std::cout << "4. Algorytm Prima" << std::endl;
        std::cout << "5. Algorytm Kruskala" << std::endl;
        std::cout << "0. Powrot" << std::endl;
        int option;
        std::cin >> option;
        std::string fileName;
        switch (option) {
            case 1:
            {if (matrix != nullptr) delete matrix;
                if (list != nullptr) delete list;
                std::cout << "Podaj ilosc wierzcholkow" << std::endl;
                int vertices;
                std::cin >> vertices;
                std::cout << "Podaj gestosc w procentach" << std::endl;
                int density;
                std::cin >> density;
                GenerateGraph generator;
                EdgesWrap edgeWrap = generator.generateEdgeList(vertices, density);  // density in percentage
                // Transformacja na macierz incydencji i listę sąsiedztwa
                TransformGenerated transformer;
                matrix = new IncidenceMatrix(transformer.transformToMatrix(&edgeWrap));
                list = new AdjacencyList(transformer.transformToList(&edgeWrap));
                break;}
            case 2:{
                if (matrix != nullptr) delete matrix;
                if (list != nullptr) delete list;
                std::cout << "Podaj nazwe pliku: ";
                std::cin >> fileName;
                try {
                    EdgesWrap edgeWrap = ReadGraph::readGraph(fileName);
                    // Transformacja na macierz incydencji i listę sąsiedztwa
                    TransformGenerated transformer;
                    matrix = new IncidenceMatrix(transformer.transformToMatrix(&edgeWrap));
                    list = new AdjacencyList(transformer.transformToList(&edgeWrap));
                } catch (const std::exception& e) {
                    std::cerr << "Blad: " << e.what() << std::endl;
                }
                break;
            }
            case 3:
                matrix->print();
                list->print();
                break;
            case 4:{
                std::cout << "Matrix:" << std::endl;
                EdgesWrap wrapMatrix = Prim::getMST(matrix);
                wrapMatrix.print();
                std::cout << std::endl << "List:" << std::endl;
                EdgesWrap wrapList = Prim::getMST(list);
                wrapList.print();
                break;}
            case 5:{
                std::cout << "Matrix:" << std::endl;
                EdgesWrap wrapMatrix = Kruskal::getMST(matrix);
                wrapMatrix.print();
                std::cout << std::endl << "List:" << std::endl;
                EdgesWrap wrapList = Kruskal::getMST(list);
                wrapList.print();
                break;}
            case 0:
                return;
        }
    }
}

void Menu::SptMenu() {
    IncidenceMatrix* matrix = nullptr;
    AdjacencyList* list = nullptr;
    while (true) {
        std::cout << "Operacje dla grafow:" << std::endl;
        std::cout << "1. Generuj graf losowo" << std::endl;
        std::cout << "2. Wczytaj graf z pliku" << std::endl;
        std::cout << "3. Wyswietl poczatkowy graf" << std::endl;
        std::cout << "4. Algorytm Dijkstry" << std::endl;
        std::cout << "5. Algorytm Bellmana-Forda" << std::endl;
        std::cout << "0. Powrot" << std::endl;
        int option;
        std::cin >> option;
        std::string fileName;
        switch (option) {
            case 1:
            {
                if (matrix != nullptr) delete matrix;
                if (list != nullptr) delete list;
                std::cout << "Podaj ilosc wierzcholkow" << std::endl;
                int vertices;
                std::cin >> vertices;
                std::cout << "Podaj gestosc w procentach" << std::endl;
                int density;
                std::cin >> density;
                GenerateGraph generator;
                EdgesWrap edgeWrap = generator.generateEdgeList(vertices, density);  // density in percentage
                // Transformacja na macierz incydencji i listę sąsiedztwa
                TransformGenerated transformer;
                matrix = new IncidenceMatrix(transformer.transformToMatrix(&edgeWrap));
                list = new AdjacencyList(transformer.transformToList(&edgeWrap));

                break;
            }
            case 2:{
                if (matrix != nullptr) delete matrix;
                if (list != nullptr) delete list;
                std::cout << "Podaj nazwe pliku: ";
                std::cin >> fileName;
                try {
                    EdgesWrap edgeWrap = ReadGraph::readGraph(fileName);
                    // Transformacja na macierz incydencji i listę sąsiedztwa
                    TransformGenerated transformer;
                    matrix = new IncidenceMatrix(transformer.transformToMatrix(&edgeWrap));
                    list = new AdjacencyList(transformer.transformToList(&edgeWrap));
                } catch (const std::exception& e) {
                    std::cerr << "Blad: " << e.what() << std::endl;
                }
                break;
            }
            case 3:
                if (matrix) matrix->print();
                if (list) list->print();
                break;
            case 4:
            {
                if (!matrix || !list) {
                    std::cout << "Graf nie został jeszcze wczytany ani wygenerowany." << std::endl;
                    break;
                }
                std::cout << "Podaj wierzcholek startowy:" << std::endl;
                int startVertex;
                std::cin >> startVertex;
                std::cout << "Podaj wierzcholek koncowy:" << std::endl;
                int endVertex;
                std::cin >> endVertex;
                std::cout << "Matrix:" << std::endl;
                EdgesWrap wrapMatrix = Dijkstra::getSPT(matrix, startVertex);
                wrapMatrix.print();
                Dijkstra::printPath(wrapMatrix, startVertex, endVertex);
                std::cout << std::endl << "List:" << std::endl;
                EdgesWrap wrapList = Dijkstra::getSPT(list, startVertex);
                wrapList.print();
                Dijkstra::printPath(wrapList, startVertex, endVertex);
                break;
            }
            case 5:
            {
                if (!matrix || !list) {
                    std::cout << "Graf nie został jeszcze wczytany ani wygenerowany." << std::endl;
                    break;
                }
                std::cout << "Podaj wierzcholek startowy:" << std::endl;
                int startVertex;
                std::cin >> startVertex;
                std::cout << "Podaj wierzcholek koncowy:" << std::endl;
                int endVertex;
                std::cin >> endVertex;
                std::cout << "Matrix:" << std::endl;
                EdgesWrap wrapMatrix = BellmanFord::getSPT(matrix, startVertex);
                wrapMatrix.print();
                BellmanFord::printPath(wrapMatrix, startVertex, endVertex);
                std::cout << std::endl << "List:" << std::endl;
                EdgesWrap wrapList = BellmanFord::getSPT(list, startVertex);
                wrapList.print();
                BellmanFord::printPath(wrapList, startVertex, endVertex);
                break;
            }
            case 0:
                return;
        }
    }
}

