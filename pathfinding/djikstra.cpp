#include "pathfinding.hpp"


// No memory allocation is done here except allocating the return
//   vector.
std::vector<GraphEdge>* path_djikstra( std::vector<GraphNode*>* allNodes,
                                       GraphNode *start, GraphNode *end
                                       #ifdef USE_THREADS
                                       ,
                                       int numThreads = 0
                                       #endif
                                       ) {
  // Mark all nodes as unvisited.
  for (std::vector<GraphNode*>::iterator i = allNodes->begin();
       i != allNodes->end();
       i++) {
    (*i)->visited(false);
  }
  end->initDistance(EDGE_MAX);

  // Start with the beginning node.
  start->visited();
  start->initDistance(0);
  std::vector<GraphEdge> queue;
  queue.push_back(GraphEdge(NULL,start,0));

  GraphEdge edge;
  GraphNode *curr;
  while (queue.size() > 0) {
    edge = queue[0];
    curr = edge.to;
    queue.erase(queue.begin()); // It's a queue, really.
    // debug
    std::cout << "Next in queue: cost(" << edge.cost << ")" << std::endl;
    curr->dump();

    // Queue all the node's (unvisited) neighbors.
    for (std::vector<GraphEdge>::iterator n = curr->begin();
         n != curr->end();
         n++) {
      if ((*n).to == NULL) continue;
      if ((*n).to->isVisited()) continue;

      (*n).to->checkDistance(curr->distance()+(*n).cost,*n);
      queue.push_back(*n);
      std::cout << "  Queueing(" << edge.cost << ")" << std::endl;
      (*n).to->dump();

    }

    // Mark the current node visited.
    curr->visited();
    if (curr == end) {
      break;
    }
  }

  // If curr != end, there is no (known) path.

  // Work backwards from the end node to get the path.
  std::vector<GraphEdge>* path = new std::vector<GraphEdge>;
  GraphEdge *p = &edge;
  while (p->to != start) {
    path->insert(path->begin(),*p);
  }

  return path;
}
