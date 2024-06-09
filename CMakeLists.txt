cmake_minimum_required(VERSION 3.28)
project(AIZO_P2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(AIZO_P2 main.cpp
        Graph/IncidenceMatrix.cpp
        Graph/IncidenceMatrix.h
        Graph/AdjacencyList.cpp
        Graph/AdjacencyList.h
        Utils/GenerateGraph.cpp
        Utils/GenerateGraph.h
        Utils/TransformGenerated.cpp
        Utils/TransformGenerated.h
        Utils/EdgesWrap.h
        Algorithms/MST/Prim.cpp
        Algorithms/MST/Prim.h
        Algorithms/MST/Kruskal.cpp
        Algorithms/MST/Kruskal.h
        Algorithms/SPT/Dijkstra.cpp
        Algorithms/SPT/Dijkstra.h
        Algorithms/SPT/BellmanFord.cpp
        Algorithms/SPT/BellmanFord.h
        Utils/Menu.h
        Utils/Menu.cpp
        Utils/ReadGraph.cpp
        Utils/ReadGraph.h
        Utils/Test.h
        Utils/Test.cpp
)
