#include <float.h>
#define EdgeCost float
#define EDGE_MAX FLT_MAX
#define EDGE_FAR FLT_MAX/2

#include "RectangularGraph.hpp"
#include "pathfinding.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

// rand()
#include <stdlib.h>
#include <time.h>


void dumpMatrix( RectangularGraphNode*** m, int rows, int cols );
int32_t GraphNode::next_issue_id = 0;

int main( int argc, char **argv ) { 

  int rows = 10,
    cols = 10;
  bool random_costs = false;
  bool random_start = true,
    random_end = true;
  time_t seed;
  int startx,starty,endx,endy;

  for (int i=1; i<argc; i++) {
    stringstream parser(stringstream::in);
    // args that take parameters
    if (string("--rows") == argv[i] && i+1 < argc) {
      parser.str(argv[++i]);
      parser >> rows;
    } else if (string("--columns") == argv[i] && i+1 < argc) {
      parser.str(argv[++i]);
      parser >> cols;
    } else if (string("--start-x") == argv[i] && i+1 < argc) {
      parser.str(argv[++i]);
      parser >> startx;
      random_start = false;
    } else if (string("--end-x") == argv[i] && i+1 < argc) {
      parser.str(argv[++i]);
      parser >> endx;
      random_end = false;
    } else if (string("--start-y") == argv[i] && i+1 < argc) {
      parser.str(argv[++i]);
      parser >> starty;
      random_start = false;
    } else if (string("--end-y") == argv[i] && i+1 < argc) {
      parser.str(argv[++i]);
      parser >> endy;
      random_end = false;

    // boolean args
    } else if (string("--random-start") == argv[i]) {
      random_start = true;
    } else if (string("--random-end") == argv[i]) {
      random_end = true;
    } else if (string("--random-costs") == argv[i]) {
      random_costs = true;
    }
  }

  time(&seed);
  srand(seed);
  if (random_start) {
    startx = rand() % cols;
    starty = rand() % rows;
  }
  if (random_end) {
    endx = rand() % cols;
    endy = rand() % rows;
  }

  cout << "Configuration:" << endl
       << "  Grid Dimension: " << rows << " x " << cols << endl
       << "  Random Costs:   " << (random_costs?"true":"false") << endl
       << "  Start Node:     " << (random_start?"[Random] ":"")
                               << "(" << startx << "," << starty << ")" << endl
       << "  End Node:       " << (random_end?"[Random] ":"")
                               << "(" << endx << "," << endy << ")" << endl
       << endl;
  

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

        if (x-1 >= 0) {
          matrix[x][y]->southwest(matrix[x-1][y-1],1.414);
        } else if (x+1 < cols) {
          matrix[x][y]->southeast(matrix[x+1][y-1],1.414);
        }
      }
      if (y+1 < rows) {
        matrix[x][y]->north(matrix[x][y+1],1);

        if (x-1 >= 0) {
          matrix[x][y]->northwest(matrix[x-1][y+1],1.414);
        } else if (x+1 < cols) {
          matrix[x][y]->northeast(matrix[x+1][y+1],1.414);
        }
      }

      int idx=0;
      for (vector<GraphEdge>::iterator i = 
             matrix[x][y]->getAdjacentNodes().begin();
           i != matrix[x][y]->getAdjacentNodes().end();
           i++) {
        cout << "[" << matrix[x][y] << "] ("
             << x << "," << y << ") Edge #" << idx++ << ":" << endl
             << "  To:   "; if ((*i).to) (*i).to->dump(); cout << endl;
        cout << "  From: "; if ((*i).from) (*i).from->dump(); cout << endl;
        cout << "  Cost: " << (*i).cost << endl;
      }

    }
  }


  if (random_costs) dumpMatrix(matrix,rows,cols);


  RectangularGraphNode
    *a = matrix[startx][starty],
    *b = matrix[endx][endy];

  RectangularGraph g;
  g.getAllNodes() = nodeList;
  std::vector<GraphEdge> *rpath =
    path_djikstra(g,a,b);

  cout << endl << g.asText(a,b,rpath) << endl;

  RectangularGraphNode *start = (RectangularGraphNode*)(rpath->front().from);
  std::cout <<"(" << start->x << "," << start->y << ")";
  for (std::vector<GraphEdge>::iterator c = rpath->begin();
       c != rpath->end();
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
