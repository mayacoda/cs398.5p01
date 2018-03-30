
#ifndef DZ04_MAP_H
#define DZ04_MAP_H


#include "Graph.h"

class Map: public BaseGameEntity  {
private:
    Graph* m_graph;
    int m_columns;
    int m_rows;
    std::list<MapNode*> m_obstacles;

public:
    Map(int h, int w);

    virtual ~Map() {
        delete m_graph;
    };

    MapNode* getNodeByPosition(Vector2D<double> pos) const;

    Graph* getGraph() const { return m_graph; }

    std::list<MapNode*> getObstacles() const { return m_obstacles; }

    void render() const override;
};


#endif //DZ04_MAP_H
