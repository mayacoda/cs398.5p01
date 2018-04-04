
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

    m_textureMeta = TextureMetadata();

    switch (terrainFlag) {
        case forest:
            m_textureMeta.set(TextureMetadata::forest);
            break;
        case mountain:
            m_textureMeta.set(TextureMetadata::mountains);
            break;
        case water:
            m_textureMeta.set(TextureMetadata::water);
            break;
        default:
        case none:
            m_textureMeta.set(TextureMetadata::none);
            break;
    }
}

void MapNode::render() const {
    glBindTexture(GL_TEXTURE_2D, MapGraphicsHelper::getInstance().getTextureId(m_textureMeta));

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

void MapNode::parseTextureMatrix(int matrix[][3]) {
    m_textureMeta.parseTextureMatrix(matrix);
}
