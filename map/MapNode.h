
#ifndef DZ04_GAMENODE_H
#define DZ04_GAMENODE_H


#ifdef _WIN32
#include <GL\glut.h>
#elif __APPLE__

#include <OpenGL/OpenGL.h>
#include <iostream>

#endif


#include "GraphNode.h"
#include "../geometry/Vector2D.h"
#include "../game-world/BaseGameEntity.h"
#include "../helpers/globals.h"
#include "../graphics/opengl_helpers.h"
#include "../graphics/texture-metadata.h"

class MapNode : public GraphNode, public BaseGameEntity {
public:
    enum terrainType {
        none,
        forest,
        mountain,
        water
    };

private:

    terrainType m_terrainFlag;

    Color m_color;

    TextureMetadata m_textureMeta;

public:

    MapNode() : GraphNode(invalid_index),
                BaseGameEntity(globals::tile, Vector2D<double>(), 0),
                m_terrainFlag(none),
                m_textureMeta(),
                m_color() {}

    MapNode(int index,
            const Vector2D<double>
            &position,
            terrainType terrainFlag);

    void render() const override;

    bool isTraversable() const {
        return m_terrainFlag != water;
    }

    void parseTextureMatrix(int matrix[3][3]);


    terrainType getTerrain() const { return m_terrainFlag; }
};


#endif //DZ04_GAMENODE_H
