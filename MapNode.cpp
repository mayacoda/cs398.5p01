
#include "MapNode.h"

MapNode::MapNode(int index,
                 const Vector2D<double> &position,
                 MapNode::terrainType terrainFlag) : GraphNode(index),
                                                     BaseGameEntity(globals::entityTypes::tile,
                                                                    position,
                                                                    0),
                                                     m_terrainFlag(terrainFlag),
                                                     m_color() {

    m_color = Color(0.3, 0.3, 0.3);
    switch (terrainFlag) {
        case forrest:
            m_color = Color(0.2, 0.9, 0.6);
            break;
        case mountain:
            m_color = Color(0.8, 0.5, 0.5);
            break;
        case water:
            m_color = Color(0.3, 0.5, 0.8);
            break;
    }
}

void MapNode::render() const {
    if (m_mark) {
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_POLYGON);
        glVertex2d(m_pos.x + 10, m_pos.y + 10);
        glVertex2d(m_pos.x - 10, m_pos.y + 10);
        glVertex2d(m_pos.x - 10, m_pos.y - 10);
        glVertex2d(m_pos.x + 10, m_pos.y - 10);
        glEnd();
    }

    int halfSize = globals::TILE_SIZE/2;
    glPushMatrix();
    glTranslated(m_pos.x, m_pos.y, 0);
    glBegin(GL_POLYGON);
    glColor3d(m_color.r, m_color.g, m_color.b);
    glVertex2d(-halfSize, -halfSize);
    glVertex2d(halfSize, -halfSize);
    glVertex2d(halfSize, halfSize);
    glVertex2d(-halfSize, halfSize);
    glEnd();
    glPopMatrix();
}
