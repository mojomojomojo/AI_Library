#include "pathfinding.hpp"

#include <queue>

using namespace std;

vector<GraphEdge>* path_astar( Graph& graph,
                               GraphNode *start, GraphNode *end,
                               int heur_comp( GraphEdge *a, GraphEdge *b )
                               )
{
  // Initialize the graph:
  //   all distances are far, except to 'end', which is infinite
  //   all nodes have not been visited or queued
  for (vector<GraphNode*>::iterator i = graph.allNodes().begin();
       i != graph.allNodes().end();
       i++) {
    (*i)->visited(false);
    (*i)->queued(false);
    (*i)->distance(EDGE_FAR);
  }

  priority_queue< GraphEdge, vector<GraphEdge>, heur_comp(a,b) > queue;
  queue.push(GraphEdge(NULL,start,0)); // queue the start node

  while (queue.size()) {
    GraphEdge path_here = queue.pop();
    GraphNode* curr = path_here.to;
    if (!curr) continue;

    // check every edge leaving 'curr'
    for (vector<GraphEdge>::iterator e = curr->begin();
         e != curr->end();
         e++) {

      

      to->checkDistance(from->distance()+e.cost, e);
    }

    
  }
}
