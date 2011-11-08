#include "graph.hpp"

class RectangularGraphNode;

// class RectangularGraphEdge : public GraphEdge {
// public:
//   EdgeCost cost;
//   RectangularGraphNode *to;
//   RectangularGraphNode *from;
//   RectangularGraphEdge()
//     : to(NULL), from(NULL), cost(EDGE_MAX) {}
//   RectangularGraphEdge(GraphEdge& e)
//     : cost(e.cost) {
//     to = e.to;
//     from = e.from;
//   }
  
// };

class RectangularGraphNode : public GraphNode {
public:
  GraphEdge& north( RectangularGraphNode *n, EdgeCost c ) {
    neighbors[North].to = n;
    neighbors[North].from = this;
    neighbors[North].cost = c;
    return this->north();
  }
  inline GraphEdge& north() { return neighbors[North]; }

  GraphEdge& east( RectangularGraphNode *n, EdgeCost c ) {
    neighbors[East].to = n;
    neighbors[East].from = this;
    neighbors[East].cost = c;
    return this->east();
  }
  inline GraphEdge& east() { return neighbors[East]; }

  GraphEdge& south( RectangularGraphNode *n, EdgeCost c ) {
    neighbors[South].to = n;
    neighbors[South].from = this;
    neighbors[South].cost = c;
    return this->south();
  }
  inline GraphEdge& south() { return neighbors[South]; }

  GraphEdge& west( RectangularGraphNode *n, EdgeCost c ) {
    neighbors[West].to = n;
    neighbors[West].from = this;
    neighbors[West].cost = c;
    return this->west();
  }
  inline GraphEdge& west() { return neighbors[West]; }

  static const int North = 0;
  static const int East = 1;
  static const int South = 2;
  static const int West = 3;

  RectangularGraphNode( int32_t x_pos, int32_t y_pos ) {
    for (int i=0; i<4; i++) {
      neighbors.push_back(GraphEdge());
    }
    x = x_pos;
    y = y_pos;
  }


  virtual void dump() {
    std::cout << "[RectNode ID(" << _id << ") (" 
              << x << "," << y << ") ";
    RectangularGraphNode *to;
    if (north().to != NULL) {
      to = (RectangularGraphNode*)north().to;
      std::cout << "N[(" << to->x << "," << to->y
                << ") " << north().cost << "] ";
    }
    if (east().to != NULL) {
      to = (RectangularGraphNode*)east().to;
      std::cout << "E[(" << to->x << "," << to->y
                << ") " << east().cost << "] ";
    }
    if (south().to != NULL) {
      to = (RectangularGraphNode*)south().to;
      std::cout << "S[(" << to->x << "," << to->y
                << ") " << south().cost << "] ";
    }
    if (west().to != NULL) {
      to = (RectangularGraphNode*)west().to;
      std::cout << "W[(" << to->x << "," << to->y
                << ") " << west().cost << "] ";
    }

    std::cout << "V(" << isVisited() << ") D(" << distance() << ") Prev(";
    GraphEdge e = _previousEdge;
    if (e.from != NULL) {
      std::cout << "[(" << ((RectangularGraphNode*)(e.from))->x << ","
                << ((RectangularGraphNode*)(e.from))->y << ") "
                << e.cost << "]";
    }
    std::cout << ")";

    std::cout << "]";
  }


  int32_t x;
  int32_t y;

protected:

};

