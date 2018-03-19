
#ifndef DZ04_ASTAR_H
#define DZ04_ASTAR_H


#include "Path.h"
#include "Graph.h"

class AStar {
public:

    static Path* shortestPath(Graph* graph, MapNode* start, MapNode* finish);
};


#endif //DZ04_ASTAR_H
