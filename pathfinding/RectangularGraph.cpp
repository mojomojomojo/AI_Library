#include "RectangularGraph.hpp"


std::string RectangularGraph::asText() {
  return asText(NULL,NULL,NULL);
}

std::string RectangularGraph::asText(
    GraphNode* start,
    GraphNode* end,
    std::vector<GraphEdge>* path
) {
  std::stringstream s(std::stringstream::out);
  RectangularGraphNode *rstart = (RectangularGraphNode*)start,
    *rend = (RectangularGraphNode*)end;

  int32_t minx,maxx,miny,maxy;
  minx = maxx = ((RectangularGraphNode*)allNodes.front())->x;
  miny = maxy = ((RectangularGraphNode*)allNodes.front())->y;

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
    *p = ' ';
    if ((*i)->isQueued()) *p = '.';
    if ((*i)->isVisited()) *p = '*';
  }
  if (rstart) marked[rstart->x][rstart->y] = '@';
  if (path) {
    // Start at the second node. The first one has been marked (@) already.
    for (std::vector<GraphEdge>::iterator e = path->begin();
         e != path->end();
         e++) {
      RectangularGraphNode *r = (RectangularGraphNode*)((*e).to);
      marked[r->x][r->y] = '+';
    }
  }
  if (rend) marked[rend->x][rend->y] = 'X'; 

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


void RectangularGraphNode::dump() {
  std::cout << "[RectNode ID(" 
            << std::setw(6) << std::setfill('0') << _id << ") (" 
            << x << "," << y << ") ";
  RectangularGraphNode *to;
  if (north().to != NULL) {
    to = (RectangularGraphNode*)(north().to);
    std::cout << "N[(" << to->x << "," << to->y
              << ") " << north().cost << "] ";
  }
  if (northeast().to != NULL) {
    to = (RectangularGraphNode*)(northeast().to);
    std::cout << "NE[(" << to->x << "," << to->y
              << ") " << northeast().cost << "] ";
  }
  if (east().to != NULL) {
    to = (RectangularGraphNode*)(east().to);
    std::cout << "E[(" << to->x << "," << to->y
              << ") " << east().cost << "] ";
  }
  if (southeast().to != NULL) {
    to = (RectangularGraphNode*)(southeast().to);
    std::cout << "SE[(" << to->x << "," << to->y
              << ") " << southeast().cost << "] ";
  }
  if (south().to != NULL) {
    to = (RectangularGraphNode*)(south().to);
    std::cout << "S[(" << to->x << "," << to->y
              << ") " << south().cost << "] ";
  }
  if (southwest().to != NULL) {
    to = (RectangularGraphNode*)(southwest().to);
    std::cout << "SW[(" << to->x << "," << to->y
              << ") " << southwest().cost << "] ";
  }
  if (west().to != NULL) {
    to = (RectangularGraphNode*)(west().to);
    std::cout << "W[(" << to->x << "," << to->y
              << ") " << west().cost << "] ";
  }
  if (northwest().to != NULL) {
    to = (RectangularGraphNode*)(northwest().to);
    std::cout << "NW[(" << to->x << "," << to->y
              << ") " << northwest().cost << "] ";
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

