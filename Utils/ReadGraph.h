
#ifndef AIZO_P2_READGRAPH_H
#define AIZO_P2_READGRAPH_H
#include <fstream>
#include <sstream>
#include "EdgesWrap.h"

class ReadGraph {
public:
   static EdgesWrap readGraph(const std::string& filename);
};
#endif //AIZO_P2_READGRAPH_H