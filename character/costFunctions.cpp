#include "costFunctions.h"
#include "../map/GraphEdge.h"

double basicCost(const GraphEdge& edge) {
    return edge.getCost();
}
