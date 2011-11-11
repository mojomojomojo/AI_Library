#ifndef __pathfinding_hpp__
#define __pathfinding_hpp__

#include "graph.hpp"
#include <vector>

std::vector<GraphEdge>* path_djikstra( Graph& g,
                                       GraphNode *start, GraphNode *end
                                       #ifdef USE_THREADS
                                       ,
                                       int32_t numThreads = 0
                                       #endif
                                       );



std::vector<GraphEdge>*
path_astar(
    Graph& g,
    GraphNode *start, GraphNode *end
);


#endif
