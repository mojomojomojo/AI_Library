#ifndef __RECTANGULARGRAPH_HPP__
#define __RECTANGULARGRAPH_HPP__

#include "graph.hpp"

#include<limits>

#define ID_FMT(x) std::setw(6) << std::setfill('0') << x


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

#define KNOWN_EDGE(name,cname)                                    \
  inline GraphEdge& name( RectangularGraphNode *r, EdgeCost c ) { \
  neighbors[cname].to = r;                                        \
  neighbors[cname].from = this;                                   \
  neighbors[cname].cost = c;                                      \
  return this->name();                                            \
  }                                                               \
  inline GraphEdge& name() { return neighbors[cname]; }


class RectangularGraphNode : public GraphNode {
public:
  inline GraphEdge& north( RectangularGraphNode *n, EdgeCost c ) {
    neighbors[North].to = n;
    neighbors[North].from = this;
    neighbors[North].cost = c;
    return this->north();
  }
  inline GraphEdge& north() { return neighbors[North]; }

  inline GraphEdge& northeast( RectangularGraphNode *n, EdgeCost c ) {
    neighbors[NorthEast].to = n;
    neighbors[NorthEast].from = this;
    neighbors[NorthEast].cost = c;
    return this->northeast();
  }
  inline GraphEdge& northeast() { return neighbors[NorthEast]; }

  inline GraphEdge& northwest( RectangularGraphNode *n, EdgeCost c ) {
    neighbors[NorthWest].to = n;
    neighbors[NorthWest].from = this;
    neighbors[NorthWest].cost = c;
    return this->northwest();
  }
  inline GraphEdge& northwest() { return neighbors[NorthWest]; }

  inline GraphEdge& east( RectangularGraphNode *n, EdgeCost c ) {
    neighbors[East].to = n;
    neighbors[East].from = this;
    neighbors[East].cost = c;
    return this->east();
  }
  inline GraphEdge& east() { return neighbors[East]; }

  inline GraphEdge& south( RectangularGraphNode *n, EdgeCost c ) {
    neighbors[South].to = n;
    neighbors[South].from = this;
    neighbors[South].cost = c;
    return this->south();
  }
  inline GraphEdge& south() { return neighbors[South]; }

  inline GraphEdge& southeast( RectangularGraphNode *n, EdgeCost c ) {
    neighbors[SouthEast].to = n;
    neighbors[SouthEast].from = this;
    neighbors[SouthEast].cost = c;
    return this->southeast();
  }
  inline GraphEdge& southeast() { return neighbors[SouthEast]; }

  inline GraphEdge& southwest( RectangularGraphNode *n, EdgeCost c ) {
    neighbors[SouthWest].to = n;
    neighbors[SouthWest].from = this;
    neighbors[SouthWest].cost = c;
    return this->southwest();
  }
  inline GraphEdge& southwest() { return neighbors[SouthWest]; }

  inline GraphEdge& west( RectangularGraphNode *n, EdgeCost c ) {
    neighbors[West].to = n;
    neighbors[West].from = this;
    neighbors[West].cost = c;
    return this->west();
  }
  inline GraphEdge& west() { return neighbors[West]; }

  static const int North = 0;
  static const int East = 2;
  static const int South = 4;
  static const int West = 6;
  static const int NorthEast = 1;
  static const int NorthWest = 7;
  static const int SouthEast = 3;
  static const int SouthWest = 5;

  inline RectangularGraphNode( int32_t x_pos, int32_t y_pos ) {
    for (int i=0; i<NumDirections; i++) {
      neighbors.push_back(GraphEdge(this,NULL,EDGE_FAR));
    }
    x = x_pos;
    y = y_pos;
  }

  virtual void dump();


  int32_t x;
  int32_t y;

protected:
  static const size_t NumDirections = 8;
};

class RectangularGraph : public Graph {
public:
  virtual std::string asText();
  virtual std::string asText( GraphNode* start,
                              GraphNode* end,
                              std::vector<GraphEdge>* path );

protected:
  
};

#endif
