
#include "Graph.h"

void Graph::setNodes(const std::vector<MapNode*> &nodes) {
    m_nodes.empty();
    m_edges.empty();

    m_nodes = nodes;
    for (int i = 0; i < nodes.size(); i++) {
        m_edges.push_back(std::list<GraphEdge>());
    }
}

void Graph::addNode(MapNode* node) {
    m_nodes.push_back(node);
    m_edges.push_back(std::list<GraphEdge>());
}

void Graph::addEdge(const GraphEdge &edge) {
    std::list<GraphEdge> fromList = m_edges[edge.getFrom()];
    std::list<GraphEdge> toList   = m_edges[edge.getTo()];

    if (edge.getFrom() == edge.getTo()) {
        return;
    }

    for (std::list<GraphEdge>::const_iterator i = fromList.begin(); i != fromList.end(); ++i) {
        if ((*i) == edge) {
            return;
        }
    }

    for (std::list<GraphEdge>::const_iterator i = toList.begin(); i != toList.end(); ++i) {
        if ((*i) == edge) {
            return;
        }
    }

    m_edges[edge.getFrom()].push_back(edge);
}

void Graph::render() const {
    for (unsigned int i = 0; i < m_nodes.size(); i++) {
        m_nodes.at(i)->render();
    }

    for (unsigned int i = 0; i < m_edges.size(); i++) {
        std::list<GraphEdge>                 list = m_edges.at(i);
        std::list<GraphEdge>::const_iterator iterator;

        for (iterator = list.begin(); iterator != list.end(); ++iterator) {
            (*iterator).render();
        }
    }
}

