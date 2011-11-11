#ifndef __graph_hpp__
#define __graph_hpp__

#include "types.hpp"

#include <stdint.h>

#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#ifdef _DEBUG
#define DEBUG(m) std::cout << m;
#else
#define DEBUG(m)
#endif

#ifdef _VERBOSE_DEBUG
#define VERBOSE_DEBUG(m) m
#else
#define VERBOSE_DEBUG(m)
#endif

#ifdef USE_THREADS
#include <pthread>

#define LOCK_NODE()                            \
  if (int rc = pthread_mutex_lock(&_lock)) {                         \
    std::cout << "pthread_mutex_lock() fails! (" << rc << ") [" <<   \
      __FILE__ << "] " << __FUNCTION__ << ":" << __LINE__ << endl;   \
    exit(rc);                                                        \
  }

#define UNLOCK_NODE()                                                  \
  if (int rc = pthread_mutex_unlock(&_lock)) {                         \
    std::cout << "pthread_mutex_unlock() fails! (" << rc << ") [" <<   \
      __FILE__ << "] " << __FUNCTION__ << ":" << __LINE__ << endl;     \
    exit(rc);                                                          \
  }

#define INIT_NODE_LOCK()                                                \
  if (int rc = pthread_mutex_init(&_lock,NULL)) {                       \
    std::cout << "pthread_mutex_init() fails! (" << rc << ") [" <<      \
      __FILE__ << "] " << __FUNCTION__ << ":" << __LINE__ << endl;      \
    exit(rc);                                                           \
  }

#define NUM_THREADS(n) n


#else // USE_THREADS

#define LOCK_NODE()
#define UNLOCK_NODE()
#define INIT_NODE_LOCK()

#define NUM_THREADS(n)

#endif


class GraphNode;

// No dynamic memory allocation takes place with this class.
class GraphEdge {
public:
  EdgeCost cost;
  GraphNode *to;
  GraphNode *from;
  GraphEdge() : to(NULL), from(NULL), cost(EDGE_FAR) {}
  GraphEdge( const GraphEdge& e)
    : to(e.to), from(e.from), cost(e.cost) {}
  GraphEdge( GraphNode *f, GraphNode *t, EdgeCost c )
    : from(f), to(t), cost(c) {}
};


class GraphNode {
protected:
  std::vector<GraphEdge> neighbors;

  int32_t _id;

  // for pathfinding
  EdgeCost _distance;
  GraphEdge _previousEdge;
  bool _visited;
  bool _queued;
  #ifdef USE_THREADS
  pthread_mutex_t _lock;
  #endif

public:
  static int32_t next_issue_id;

  GraphNode()
    : _previousEdge(NULL,NULL,EDGE_FAR) {
    INIT_NODE_LOCK();
    _visited = false;
    _queued = false;
    _distance = EDGE_FAR;
    _id = GraphNode::next_issue_id++;
  }

  virtual std::vector<GraphEdge>& getAdjacentNodes() {
    return neighbors;
  }
  virtual std::vector<GraphEdge>::iterator begin() {
    return neighbors.begin();
  }
  virtual std::vector<GraphEdge>::iterator end() {
    return neighbors.end();
  }
  virtual void connectNode( GraphNode *to, EdgeCost cost ) {
    return neighbors.push_back(GraphEdge(this,to,cost));
  }

  virtual void dump() {
    std::cout << "[GraphNode ID(" << _id << ") ";

    size_t i=0;
    for (std::vector<GraphEdge>::iterator e = neighbors.begin();
         e != neighbors.end();
         e++,i++) {
      std::cout << " [" << i << "]ID(" << (*e).to->_id << ")";
    }

    std::cout << "V(" << _visited << ") "
              << "D(" << _distance << ") "
              << "Prev(";
    if (_previousEdge.from != NULL) {
      std::cout << "[ID(" << (_previousEdge.from)->_id << ") "
                << _previousEdge.cost << "]";
    }
    std::cout << ")";

    std::cout << "]";
  }

  inline EdgeCost distance() { return _distance; }
  inline EdgeCost checkDistance( EdgeCost d, GraphEdge edge ) {
    LOCK_NODE();
    if (d < _distance) {
      VERBOSE_DEBUG(std::cout<<"Lower distance to ["<<std::setw(6)<<std::setfill('0')<<_id<<"] ("<<d<<") from ["<<std::setw(6)<<std::setfill('0')<<edge.from->_id<<"] (old: "<<_distance<<")"<<std::endl;)
      _distance = d;
      _previousEdge = edge;
    }
    UNLOCK_NODE();
  }
  inline void initDistance( EdgeCost d ) { _distance = d; }

  inline bool isVisited() { return _visited; }
  inline void visited( bool v = true ) { _visited = v; }

  inline bool isQueued() { return _queued; }
  inline void queued( bool v = true ) { _queued = v; }

  inline GraphEdge& previousEdge() { return _previousEdge; }

  inline int32_t& id() { return _id; }
};


// int32_t GraphNode::next_issue_id = 0;


class Graph {
public:
  Graph() {};
  std::vector<GraphNode*>& getAllNodes() { return allNodes; }

  inline virtual std::string asText() { return asText(NULL,NULL,NULL); }
  inline virtual std::string asText( GraphNode* start,
                                     GraphNode* end,
                                     std::vector<GraphEdge>* path ) {
    return std::string("[Graph]");
  }

protected:
  std::vector<GraphNode*> allNodes;
};


#endif
