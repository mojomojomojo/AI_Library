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
      neighbors.push_back(GraphEdge(this,NULL,EDGE_FAR));
    }
    x = x_pos;
    y = y_pos;
  }

  virtual void dump() {
    std::cout << "[RectNode ID(" << std::setw(6) << std::setfill('0') << _id << ") (" 
              << x << "," << y << ") ";
    RectangularGraphNode *to;
    if (north().to != NULL) {
      to = (RectangularGraphNode*)(north().to);
      std::cout << "N[(" << to->x << "," << to->y
                << ") " << north().cost << "] ";
    }
    if (east().to != NULL) {
      to = (RectangularGraphNode*)(east().to);
      std::cout << "E[(" << to->x << "," << to->y
                << ") " << east().cost << "] ";
    }
    if (south().to != NULL) {
      to = (RectangularGraphNode*)(south().to);
      std::cout << "S[(" << to->x << "," << to->y
                << ") " << south().cost << "] ";
    }
    if (west().to != NULL) {
      to = (RectangularGraphNode*)(west().to);
      std::cout << "W[(" << to->x << "," << to->y
                << ") " << west().cost << "] ";
    }

    std::cout << "V(" << isVisited() << ") D(" << distance() << ") Prev(";
    GraphEdge e = _previousEdge;
    if (e.from != NULL) {
      std::cout << "[F(" << ((RectangularGraphNode*)(e.from))->x << ","
                << ((RectangularGraphNode*)(e.from))->y << ") "
                << "T(" << ((RectangularGraphNode*)(e.to))->x << ","
                << ((RectangularGraphNode*)(e.to))->y << ") "
                << e.cost << "]";
    }
    std::cout << ")";

    std::cout << "]";
  }


  int32_t x;
  int32_t y;

protected:

};

class RectangularGraph : public Graph {
public:
  virtual std::string asText() {
    std::stringstream s(std::stringstream::out);

    int32_t minx,maxx,miny,maxy;
    for (std::vector<GraphNode*>::iterator i = allNodes.begin();
         i != allNodes.end();
         i++) {
      RectangularGraphNode *r = (RectangularGraphNode*)*i;
      if (r->x < minx) minx = r->x;
      if (r->x > maxx) maxx = r->x;
      if (r->y < miny) miny = r->y;
      if (r->y > maxy) maxy = r->y;
    }

    char **marked = new char*[maxx-minx+1];
    for (size_t i=0; i<(maxy-miny+1); i++) {
      marked[i] = new char[maxy-miny+1];
    }

    for (std::vector<GraphNode*>::iterator i = allNodes.begin();
         i != allNodes.end();
         i++) {
      RectangularGraphNode *r = (RectangularGraphNode*)*i;
      char *p = &(marked[r->x][r->y]);
      *p = '.';
      if ((*i)->isQueued()) *p = 'o';
      if ((*i)->isVisited()) *p = '*';
    }

    // top-to-bottom
    for (size_t y=(maxy-miny); y>=0; y--) {
      for (size_t x=0; x<(maxy-miny+1); x++) {
        s << marked[x][y];
      }
      s << std::endl;

      if (y==0) break;
    }

    return s.str();
  }

protected:
  
};
