#ifndef AIZO_P2_TEST_H
#define AIZO_P2_TEST_H




#include <iostream>
#include "../Graph/IncidenceMatrix.h"
#include "../Graph/AdjacencyList.h"
#include "GenerateGraph.h"
#include "TransformGenerated.h"
#include "PathInfo.h"

class Test {
public:


    void startTests();
private:
    IncidenceMatrix* matrix;
    AdjacencyList* list;
    GenerateGraph generator;
    TransformGenerated transformer;
    long long calculateTime(int algorithm);
    static void saveToCsvFile(std::string fileName, long long time , int vertexNum,float density);
    static void saveToCsvFile(std::string fileName, std::string message);
    void typeOfDataMessage(std::string message);


};


#endif //AIZO_P2_TEST_H
