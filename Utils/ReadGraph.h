
#ifndef AIZO_P2_READGRAPH_H
#define AIZO_P2_READGRAPH_H
#include <fstream>
#include <sstream>
#include "EdgesList.h"

class ReadGraph {
public:
   static EdgeList readGraph(const std::string& filename);
   //funkcja wczytywania grafu z pliku
};
#endif //AIZO_P2_READGRAPH_H
