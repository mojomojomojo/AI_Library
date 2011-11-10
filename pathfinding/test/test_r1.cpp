#include "RectangularGraph.hpp"
#include "pathfinding.hpp"

#include <iostream>
#include <iomanip>
using namespace std;

void dumpMatrix( RectangularGraphNode*** m, int rows, int cols );
int32_t GraphNode::next_issue_id = 0;

int main() { 

  int rows = 10,
    cols = 10;

  std::vector<GraphNode*> nodeList;
  RectangularGraphNode*** matrix = new RectangularGraphNode**[rows];
  for (int i=0; i<rows; i++) matrix[i] = new RectangularGraphNode*[cols];

  for (int y=0; y<rows; y++) {
    for (int x=0; x<cols; x++) {
      matrix[x][y] = new RectangularGraphNode(x,y);
      matrix[x][y]->id() = x * 1000 + y;
      nodeList.push_back(matrix[x][y]);
    }
  }
      
  for (int y=0; y<rows; y++) {
    for (int x=0; x<cols; x++) {

      if (x-1 >= 0) {
        matrix[x][y]->west(matrix[x-1][y],1);
      }
      if (x+1 < cols) {
        matrix[x][y]->east(matrix[x+1][y],1);
      }
      if (y-1 >= 0) {
        matrix[x][y]->south(matrix[x][y-1],1);
      }
      if (y+1 < rows) {
        matrix[x][y]->north(matrix[x][y+1],1);
      }

      // int idx=0;
      // for (vector<GraphEdge>::iterator i = matrix[x][y]->getAdjacentNodes().begin();
      //      i != matrix[x][y]->getAdjacentNodes().end();
      //      i++) {
      //   cout << "[" << matrix[x][y] << "] (" << x << "," << y << ") Edge #" << idx++ << ":" << endl
      //        << "  To:   " << hex << ((*i).to) << dec << endl
      //        << "  From: " << hex << ((*i).from) << dec << endl
      //        << "  Cost: " << (*i).cost << endl;
      // }
    }
  }

  //dumpMatrix(matrix,rows,cols);

  RectangularGraphNode
    *a = matrix[0][0],
    *b = matrix[cols-3][rows-4];

  RectangularGraph g;
  g.getAllNodes() = nodeList;
  std::vector<GraphEdge> *r =
    path_djikstra(g,a,b);

  RectangularGraphNode *start = (RectangularGraphNode*)(r->front().from);
  std::cout <<"(" << start->x << "," << start->y << ")";
  for (std::vector<GraphEdge>::iterator c = r->begin();
       c != r->end();
       c++) {
    RectangularGraphNode *to = (RectangularGraphNode*)((*c).to);
    std::cout << " --[" << (*c).cost << "]--> "
              << "(" << to->x << "," << to->y << ")";
  }
  std::cout << std::endl;
}

// void dumpNode( RectangularGraphNode *n ) {
//   std::cout << "[RectNode ID(" << _id << ") (" << n->x << "," << n->y << ") ";
//   RectangularGraphNode *to;
//   if (n->north().to != NULL) {
//     to = (RectangularGraphNode*)n->north().to;
//     std::cout << "N[(" << to->x << "," << to->y
//               << ") " << n->north().cost << "] ";
//   }
//   if (n->east().to != NULL) {
//     to = (RectangularGraphNode*)n->east().to;
//     std::cout << "E[(" << to->x << "," << to->y
//               << ") " << n->east().cost << "] ";
//   }
//   if (n->south().to != NULL) {
//     to = (RectangularGraphNode*)n->south().to;
//     std::cout << "S[(" << to->x << "," << to->y
//               << ") " << n->south().cost << "] ";
//   }
//   if (n->west().to != NULL) {
//     to = (RectangularGraphNode*)n->west().to;
//     std::cout << "W[(" << to->x << "," << to->y
//               << ") " << n->west().cost << "] ";
//   }

//   std::cout << "V(" << n->isVisited() << ") D(" << n->distance() << ") Prev(";
//   GraphEdge e = n->previousEdge();
//   if (e.from != NULL) {
//     std::cout << "[(" << ((RectangularGraphNode*)(e.from))->x << ","
//               << ((RectangularGraphNode*)(e.from))->y << ") "
//               << e.cost << "]";
//   }
//   std::cout << ")";

//   std::cout << "]";
// }

void dumpMatrix( RectangularGraphNode*** m, int rows, int cols ) {
  for ( int y = 0; y < rows; y++ ) {
    for ( int x = 0; x < cols; x++ ) {
      std::cout << "(" << x << "," << y << "): ";
      m[x][y]->dump();
      std::cout << std::endl;
    }
  }
}
