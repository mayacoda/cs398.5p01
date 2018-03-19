
#ifndef DZ04_GAMENODE_H
#define DZ04_GAMENODE_H


#ifdef _WIN32
#include <GL\glut.h>
#elif __APPLE__

#include <OpenGL/gl.h>
#include <iostream>

#endif


#include "GraphNode.h"
#include "Vector2D.h"
#include "BaseGameEntity.h"
#include "globals.h"
#include "opengl_helpers.h"

class MapNode : public GraphNode, public BaseGameEntity {
public:
    enum terrainType {
        none,
        forrest,
        mountain,
        water
    };

private:

    terrainType m_terrainFlag = none;

    Color m_color;

    bool m_mark;

public:

    MapNode() : GraphNode(invalid_index),
                BaseGameEntity(globals::entityTypes::tile, Vector2D<double>(), 0),
                m_terrainFlag(none),
                m_color() {}

    MapNode(int index,
            const Vector2D<double>
            &position,
            terrainType terrainFlag);

    void render() const override;

    void makeBlack() {
        m_mark = true;
        m_color = Color(0.0, 0.0, 0.0);
    }

    terrainType getTerrain() const { return m_terrainFlag; }
};


#endif //DZ04_GAMENODE_H
