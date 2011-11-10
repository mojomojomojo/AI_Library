#include "pathfinding.hpp"

#include <iomanip>

// No memory allocation is done here except allocating the return
//   vector.
std::vector<GraphEdge>* path_djikstra( Graph& graph,
                                       GraphNode *start, GraphNode *end
                                       #ifdef USE_THREADS
                                       ,
                                       int numThreads = 0
                                       #endif
                                       ) {
  // Mark all nodes as unvisited.
  for (std::vector<GraphNode*>::iterator i = graph.getAllNodes().begin();
       i != graph.getAllNodes().end();
       i++) {
    (*i)->visited(false);
    (*i)->queued(false);
  }
  end->initDistance(EDGE_MAX);

  // Start with the beginning node.
  start->initDistance(0);
  std::vector<GraphEdge> queue;
  queue.push_back(GraphEdge(NULL,start,0));

  GraphEdge edge;
  GraphNode *curr;
  while (queue.size() > 0) {
    VERBOSE_DEBUG(std::cout << "Q: "; for (size_t i=0; i<queue.size(); i++) { if (i>0) std::cout << ", "; std::cout << std::setw(6) << std::setfill('0') << queue[i].to->id(); } std::cout << std::endl;);

    std::cout << graph.asText() << std::endl;

    edge = queue[0];
    curr = edge.to;
    queue.erase(queue.begin()); // dequeue the first element off

    if (curr->isVisited()) continue; // Skip it.

    // debug
    VERBOSE_DEBUG(
        std::cout << std::endl << "Next in queue[" << queue.size() << "]: cost("
                  << edge.cost << ") ";
    curr->dump();
    std::cout << std::endl;
    );

    // Queue all the node's (unvisited) neighbors.
    for (std::vector<GraphEdge>::iterator n = curr->begin();
         n != curr->end();
         n++) {
      if ((*n).to == NULL) continue;
      if ((*n).to->isVisited()) continue;

      (*n).to->checkDistance(curr->distance()+(*n).cost,*n);
      (*n).to->queued(true); // mark it as queued (debugging)
      queue.push_back(*n);
      VERBOSE_DEBUG(
      std::cout << "  Queueing: ";
      (*n).from->dump();
      std::cout << " --(" << edge.cost << ")-> ";
      (*n).to->dump();
      std::cout << std::endl;
      )
    }

    // Mark the current node visited.
    curr->visited();
    if (curr == end) {
      //std::cout << "  At end node!" << std::endl;
      break;
    }
  }

  // If curr != end, there is no (known) path.

  //std::cout << "Path Found!" << std::endl;
  // Work backwards from the end node to get the path.
  std::vector<GraphEdge>* path = new std::vector<GraphEdge>;
  GraphEdge *p = &edge;
  while (p->from != NULL) {
    path->insert(path->begin(),*p);

    VERBOSE_DEBUG(
    std::cout << std::hex << p << std::dec << ": ";
    for(int i=0; i<path->size(); i++) {
      std::cout << "[Edge F(" << path[0][i].from->id()
                << ") T(" << path[0][i].to->id()
                << ") C(" << path[0][i].cost << ")] ";
    }
    std::cout << std::endl;
    )

    p = &(p->from->previousEdge());
  }

  return path;
}
