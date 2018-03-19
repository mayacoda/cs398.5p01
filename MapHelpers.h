#ifndef DZ04_MAPHELPERS_H
#define DZ04_MAPHELPERS_H


#include "MapNode.h"
#include "globals.h"
#include <vector>

inline std::vector<MapNode> generateTerrain(int height, int width) {
//    int columns = width / globals::TILE_SIZE;
//    int rows = height / globals::TILE_SIZE;
//
//    std::vector<MapNode> nodes;
//
//    int index = 0;
//    for (int i = 0; i < rows; i++) {
//        for (int j = 0; j < columns; j++) {
//            int terrain = iRandomRange(0, globals::MAX_TERRAIN_TYPES - 1);
//            MapNode node = MapNode(index, Vector2D<double>(i * globals::TILE_SIZE, j * globals::TILE_SIZE), terrain);
//            nodes.push_back(node);
//        }
//    }
//
//    return nodes;
}

#endif //DZ04_MAPHELPERS_H
