#include "costFunctions.h"
#include "GraphEdge.h"

double basicCost(const GraphEdge& edge) {
    return edge.getCost();
}
