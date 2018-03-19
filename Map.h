
#ifndef DZ04_MAP_H
#define DZ04_MAP_H


#include "Graph.h"

class Map: public BaseGameEntity  {
private:
    Graph* graph;
    int m_columns;
    int m_rows;

public:
    Map(int h, int w);

    MapNode* getNodeByPosition(Vector2D<double> pos) const;

    Graph* getGraph() const { return graph; }

    void render() const override;
};


#endif //DZ04_MAP_H
