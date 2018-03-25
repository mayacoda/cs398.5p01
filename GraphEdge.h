#ifndef DZ04_GRAPHEDGE_H
#define DZ04_GRAPHEDGE_H
#include <string>
#include "MapNode.h"

class GraphEdge : public BaseGameEntity {
protected:
    MapNode* to;
    MapNode* from;

    double cost;

public:

    GraphEdge(MapNode* from, MapNode* to, double cost) : to(to),
                                                         from(from),
                                                         cost(cost),
                                                         BaseGameEntity(globals::entityTypes::graph,
                                                                        Vector2D<double>(),
                                                                        0) {};


    int getTo() const { return to->getIndex(); }

    int getFrom() const { return from->getIndex(); }

    bool operator==(const GraphEdge &rhs) const {
        return to == rhs.to &&
               from == rhs.from;
    }

    bool operator!=(const GraphEdge &rhs) const {
        return !(rhs == *this);
    }

    double getCost() const { return cost; }

    void render() const override {
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex2d(to->getPos().x, to->getPos().y);
        glVertex2d(from->getPos().x, from->getPos().y);
        glEnd();

        Vector2D<double> mid = (to->getPos() + from->getPos()) / 2;
        glBegin(GL_POLYGON);
        glVertex2d(mid.x + 10, mid.y + 10);
        glVertex2d(mid.x - 10, mid.y + 10);
        glVertex2d(mid.x - 10, mid.y - 10);
        glVertex2d(mid.x + 10, mid.y - 10);
        glEnd();

        drawText(std::to_string(static_cast<long double>(cost)).substr(0, 1).c_str(), mid.x - 4, mid.y - 6, Color(1.0, 1.0, 1.0));
    }
};

#endif //DZ04_GRAPHEDGE_H
