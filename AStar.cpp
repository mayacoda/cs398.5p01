
#include <set>
#include <map>
#include "AStar.h"

double heuristicDistance(const MapNode* start, const MapNode* finish) {
    return start->getPos().distanceTo(finish->getPos());
}

MapNode* findLowestCost(std::set<MapNode*> set, std::map<int, double> fScore) {
    MapNode* lowest = nullptr;
    for (auto it = set.begin(); it != set.end(); ++it) {
        if (!lowest) {
            lowest = *it;
            continue;
        }

        if (fScore[(*it)->getIndex()] < fScore[lowest->getIndex()]) {
            lowest = *it;
        }
    }

    return lowest;
}

void fillScores(std::map<int, double>* scoreMap, std::vector<MapNode*> nodes) {
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        scoreMap->insert(std::pair<int, double>((*it)->getIndex(), std::numeric_limits<double>::infinity()));
    }
}

Path* reconstructPath(const std::map<int, MapNode*> &cameFrom, MapNode* current) {
    auto* path = new Path();
    path->loop(false);
    std::list<Vector2D<double> > list;
    list.push_back(current->getPos());

    while (cameFrom.find(current->getIndex()) != cameFrom.end()) {
        current = cameFrom.at(current->getIndex());
        list.push_back(current->getPos());
    }

    list.reverse();
    path->set(list);

    return path;
}

Path* AStar::shortestPath(Graph* graph, MapNode* start, MapNode* finish) {
    if (!finish->isTraversable()) {
        std::cout << "AStar::shortestPath: goal cannot be reached" << std::endl;
        return new Path();
    }
    
    std::vector<MapNode*>              nodes = graph->getNodes();
    std::vector<std::list<GraphEdge> > edges = graph->getEdges();

    std::set<MapNode*> closedSet;
    std::set<MapNode*> openSet;
    openSet.insert(start);

    std::map<int, MapNode*> cameFrom;
    std::map<int, double>   gScore;
    fillScores(&gScore, nodes);
    gScore[start->getIndex()] = 0;

    std::map<int, double> fScore;
    fillScores(&fScore, nodes);
    fScore[start->getIndex()] = heuristicDistance(start, finish);

    while (!openSet.empty()) {
        MapNode* current = findLowestCost(openSet, fScore);
        if (current == finish) {
            // construct the path
            return reconstructPath(cameFrom, current);
        }

        openSet.erase(current);
        closedSet.insert(current);

        auto neighbors = edges[current->getIndex()];

        for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
            GraphEdge edge = *it;
            MapNode* neighbor = nodes[edge.getTo()];
            
            if (closedSet.find(neighbor) != closedSet.end()) {
                // if the neighbor has already been added to the closedSet
                continue;
            }

            if (openSet.find(neighbor) == openSet.end()) {
                openSet.insert(neighbor);
            }

            double tentativeScore = gScore[current->getIndex()] + edge.getCost();
            
            if (tentativeScore >= gScore[neighbor->getIndex()]) {
                // neighbor isn't a better path
                continue;
            }
            
            cameFrom[neighbor->getIndex()] = current;
            gScore[neighbor->getIndex()] = tentativeScore;
            fScore[neighbor->getIndex()] = gScore[neighbor->getIndex()] + heuristicDistance(neighbor, finish);
        }
    }


    return new Path();
}
