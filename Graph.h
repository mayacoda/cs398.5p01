
#ifndef DZ04_GRAPH_H
#define DZ04_GRAPH_H


#include <vector>
#include <list>
#include <iostream>
#include "MapNode.h"
#include "GraphEdge.h"

class Graph : public BaseGameEntity {
private:
    std::vector<MapNode*>               m_nodes;
    std::vector<std::list<GraphEdge> > m_edges;

public:

    Graph() : BaseGameEntity(globals::entityTypes::graph, Vector2D<double>(-1, -1), 0),
              m_nodes(std::vector<MapNode*>()),
              m_edges(std::vector<std::list<GraphEdge> >()) {}

    void addNode(MapNode* node);

    void addEdge(const GraphEdge &edge);

    void render() const override;

    std::vector<MapNode*> getNodes() const { return m_nodes; }

    std::vector<std::list<GraphEdge> > getEdges() const { return m_edges; }

    void setNodes(const std::vector<MapNode*> &nodes);

    GraphEdge getEdge(const MapNode &from, const MapNode &to) const;
};


#endif //DZ04_GRAPH_H
