
#include "MapNode.h"
#include "MapGraphicsHelper.h"

MapNode::MapNode(int index,
                 const Vector2D<double> &position,
                 MapNode::terrainType terrainFlag) : GraphNode(index),
                                                     BaseGameEntity(globals::entityTypes::tile,
                                                                    position,
                                                                    globals::TILE_SIZE / 2),
                                                     m_terrainFlag(terrainFlag),
                                                     m_color() {

    m_color = Color(0.3, 0.3, 0.3);
    switch (terrainFlag) {
        case forest:
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
    glBindTexture(GL_TEXTURE_2D, MapGraphicsHelper::getInstance().getTextureId(m_terrainFlag));

    glEnable(GL_TEXTURE_2D);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    int halfSize = globals::TILE_SIZE/2;
    glColor3f(1, 1, 1);

    glPushMatrix();
    glTranslated(m_pos.x, m_pos.y, 0);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2d(-halfSize, -halfSize);
    glTexCoord2f(1, 0);
    glVertex2d(halfSize, -halfSize);
    glTexCoord2f(1, 1);
    glVertex2d(halfSize, halfSize);
    glTexCoord2f(0, 1);
    glVertex2d(-halfSize, halfSize);

    glEnd();

    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_TEXTURE_2D);
}
