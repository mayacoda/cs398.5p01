#include "costFunctions.h"
#include "../map/GraphEdge.h"

double basicCost(const GraphEdge& edge) {
    return edge.getCost();
}

double sneakCost(const GraphEdge &edge) {
    if (edge.getToNode()->getTerrain() == MapNode::none) return 1;

    return 0;
}

double thugCost(const GraphEdge &edge) {
    return 0;
}

double runnerCost(const GraphEdge &edge) {
    if (edge.getToNode()->getTerrain() == MapNode::none) return 0;

    return 1;
}
