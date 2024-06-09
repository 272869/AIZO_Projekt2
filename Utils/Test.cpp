#include "Test.h"
#include "EdgesWrap.h"
#include "../Algorithms/MST/Prim.h"
#include "../Algorithms/MST/Kruskal.h"
#include "../Algorithms/SPT/Dijkstra.h"
#include "../Algorithms/SPT/BellmanFord.h"
#include <fstream>
#include <chrono>


// Rozpoczęcie testów
void Test::startTests() {
    // Tablice z gęstościami i liczbą wierzchołków
    float density[] = {25,50,99};
    int vertex[] = {20,40,80,100,140,180,200};
    std::string format ="vertex, density[%], time[us]"; // Format nagłówka pliku CSV
    typeOfDataMessage(format); // Zapisanie nagłówka do plików
    // Pętle iterujące przez wszystkie kombinacje gęstości i liczby wierzchołków
    for(float d : density){
        for(int v : vertex){
            // Inicjalizacja zmiennych przechowujących czas wykonania algorytmów
            long long timePrimList=0;
            long long timePrimMatrix=0;
            long long timeKruskalList=0;
            long long timeKruskalMatrix=0;
            long long timeDijkstralList=0;
            long long timeDijkstraMatrix=0;
            long long timeFordBellmanlList=0;
            long long timeFordBellmanMatrix=0;
            // Iteracja 25 razy dla każdej kombinacji
            for(int i=0;i<25;i++){
                EdgeList edgeWrap = generator.generateEdgeList(v, d);
                matrix = new IncidenceMatrix(transformer.transformToMatrix(&edgeWrap));
                list = new AdjacencyList(transformer.transformToList(&edgeWrap));
                // Pomiar czasu dla każdego z algorytmów
                timePrimMatrix += calculateTime(1); // Algorytm Prima na macierzy
                timePrimList += calculateTime(2); // Algorytm Prima na liście
                timeKruskalMatrix += calculateTime(3); // Algorytm Kruskala na macierzy
                timeKruskalList += calculateTime(4); // Algorytm Kruskala na liście
                timeDijkstraMatrix += calculateTime(5); // Algorytm Dijkstry na macierzy
                timeDijkstralList += calculateTime(6); // Algorytm Dijkstry na liście
                timeFordBellmanMatrix+= calculateTime(7); // Algorytm Forda-Bellmana na macierzy
                timeFordBellmanlList += calculateTime(8); // Algorytm Forda-Bellmana na liście
            }
            // Zapis wyników do plików CSV
            saveToCsvFile("primList.csv",timePrimList,v,d);
            saveToCsvFile("primMatrix.csv",timePrimMatrix,v,d);
            saveToCsvFile("kruskalList.csv",timeKruskalList,v,d);
            saveToCsvFile("kruskalMatrix.csv",timeKruskalMatrix,v,d);
            saveToCsvFile("dijkstraList.csv",timeDijkstralList,v,d);
            saveToCsvFile("dijkstraMatrix.csv",timeDijkstraMatrix,v,d);
            saveToCsvFile("fordBellmanList.csv",timeFordBellmanlList,v,d);
            saveToCsvFile("fordBellmanMatrix.csv",timeFordBellmanMatrix,v,d);
        }
    }
}

// Zapisanie danych do pliku CSV
void Test::saveToCsvFile(std::string fileName, long long time , int vertexNum,float density){
    std::ofstream file(fileName,std::ios::out | std::ios::app); // Otwarcie pliku do zapisu
    if (!file.is_open()) { // Sprawdzenie, czy plik został otwarty poprawnie
        std::cerr << "Nie można otworzyć pliku " << fileName << " do zapisu!" << std::endl; // Komunikat o błędzie
        return;
    }
    double time2;
    time2 = static_cast<double>(time)/25; // Obliczenie średniego czasu
    file << vertexNum << ","<<density<<","<<time2<<std::endl; // Zapisanie danych do pliku CSV
    file.close(); // Zamknięcie pliku
}

// Zapisanie komunikatu do pliku CSV
void Test::saveToCsvFile(std::string fileName, std::string message){
    std::ofstream file(fileName,std::ios::out | std::ios::app); // Otwarcie pliku do zapisu

    if (!file.is_open()) { // Sprawdzenie, czy plik został otwarty poprawnie
        std::cerr << "Nie można otworzyć pliku " << fileName << " do zapisu!" << std::endl; // Komunikat o błędzie
        return;
    }
    file<<message<<std::endl; // Zapisanie komunikatu do pliku CSV
    file.close(); // Zamknięcie pliku
}

// Wypisanie komunikatu z formatem danych
void Test::typeOfDataMessage(std::string message){
    std::cout<<"utworzono plik"<<std::endl; // Komunikat o utworzeniu pliku
    saveToCsvFile("primList.csv",message); // Zapisanie komunikatu do pliku CSV
    //std::cout<<"utworzono plik1"<<std::endl;
    saveToCsvFile("primMatrix.csv",message); // Zapisanie komunikatu do pliku CSV
    saveToCsvFile("kruskalList.csv",message); // Zapisanie komunikatu do pliku CSV
    saveToCsvFile("kruskalMatrix.csv",message); // Zapisanie komunikatu do pliku CSV
    saveToCsvFile("dijkstraList.csv",message); // Zapisanie komunikatu do pliku CSV
    saveToCsvFile("dijkstraMatrix.csv",message); // Zapisanie komunikatu do pliku CSV
    saveToCsvFile("fordBellmanList.csv",message); // Zapisanie komunikatu do pliku CSV
    saveToCsvFile("fordBellmanMatrix.csv",message); // Zapisanie komunikatu do pliku CSV
}
/*1-primMatrix
2-primList
3-kruskalMatrix
4-kruskalList
5-dijkstraMAtrix
6-dijkstraList
7-fordBellmanMAtrix
8-fordBellmanList*/

long long Test::calculateTime(int algorithm) {
    long long time;

    auto timeStart = std::chrono::high_resolution_clock::now();
    switch (algorithm) {
        case 1:
            Prim::getMST(matrix);
            break;
        case 2:
            Prim::getMST(list);
            break;
        case 3:
            Kruskal::getMST(matrix);
            break;
        case 4:
            Kruskal::getMST(list);
            break;
        case 5:
            Dijkstra::getSPT(matrix, 0);
            break;
        case 6:
            Dijkstra::getSPT(list, 0);
            break;
        case 7:
            BellmanFord::getSPT(matrix, 0);
            break;
        case 8:
            BellmanFord::getSPT(list, 0);
            break;
        default:
            break;
    }
    auto timeEnd =std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStart).count();
    return time;
}

