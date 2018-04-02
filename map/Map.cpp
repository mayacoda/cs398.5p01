
#include <cassert>
#include "Map.h"

struct TerrainCenter {
    int                  x, y;
    MapNode::terrainType terrain;

    TerrainCenter(int x, int y, MapNode::terrainType terrain) : x(x), y(y), terrain(terrain) {}
};

double distanceTo(int x1, int x2, int y1, int y2) {
    int ySep = y1 - y2;
    int xSep = x1 - x2;

    return sqrt(static_cast<double>((xSep * xSep) + (ySep * ySep)));
}

MapNode::terrainType findClosestTerrainCenter(int row, int column, std::list<TerrainCenter> terrainCenters) {
    TerrainCenter closest         = terrainCenters.front();
    double        closestDistance = std::numeric_limits<double>::infinity();

    for (auto it = terrainCenters.begin(); it != terrainCenters.end(); ++it) {
        double currentDistance = distanceTo(row, (*it).x, column, (*it).y);
        if (currentDistance <= closestDistance) {
            closestDistance = currentDistance;
            closest         = (*it);
        }
    }

    return closest.terrain;
}

Map::Map(int h, int w) : BaseGameEntity(globals::entityTypes::terrain, Vector2D<double>(-1, -1), 0) {
    int rows    = h / globals::TILE_SIZE;
    int columns = w / globals::TILE_SIZE;

    m_rows                                   = rows;
    m_columns                                = columns;

	MapNode*** map = new MapNode**[rows];
	for (int i = 0; i < rows; i++)
	{
		map[i] = new MapNode*[columns];
	}

    std::list<TerrainCenter> terrainCenters;
    int                      numberOfCenters = 20;

    for (int i = 0; i < numberOfCenters; i++) {
//        auto terrain = static_cast<MapNode::terrainType>(iRandomRange(0, globals::MAX_TERRAIN_TYPES - 2));
        auto terrain = static_cast<MapNode::terrainType>(0);
        auto x       = iRandomRange(0, rows);
        auto y       = iRandomRange(0, columns);
        terrainCenters.push_back(TerrainCenter(x, y, terrain));
    }

    std::vector<MapNode*> nodes;

    int index = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            MapNode::terrainType terrain;

            // enclose the island with water
            if (i == 0 || j == 0 || i == rows - 1 || j == columns - 1) {
                terrain = MapNode::terrainType::water;
            } else {
                terrain = findClosestTerrainCenter(i, j, terrainCenters);
            }

            MapNode* node = new MapNode(index,
                                        Vector2D<double>(i * globals::TILE_SIZE + globals::TILE_SIZE / 2,
                                                         j * globals::TILE_SIZE + globals::TILE_SIZE / 2),
                                        terrain);
            map[i][j] = node;
            index++;

            if (!node->isTraversable()) {
                m_obstacles.push_back(node);
            }

            nodes.push_back(node);
        }
    }

    m_graph = new Graph();
    m_graph->setNodes(nodes);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            // skip if block is not traversable, it has no connections
            if (!map[i][j]->isTraversable()) continue;

            for (int x = -1; x < 2; x++) {
                for (int y = -1; y < 2; y++) {
                    // make connection to all neighbors if possible
                    if (i + x >= 0 &&
                        i + x < rows &&
                        j + y >= 0 &&
                        j + y < columns &&
                        map[i + x][j + y]->isTraversable()) {

                        m_graph->addEdge(GraphEdge(map[i][j],
                                                 map[i + x][j + y],
                                                 map[i][j]->getTerrain()));
                    }
                }
            }
        }
    }

	for (auto i = 0; i < rows; i++) {
		delete[] map[i];
	}

	delete[] map;
}

void Map::render() const {
    m_graph->render();
}

MapNode* Map::getNodeByPosition(Vector2D<double> pos) const {
    auto row    = static_cast<int>(floor(pos.x / globals::TILE_SIZE));
    auto column = static_cast<int>(floor(pos.y / globals::TILE_SIZE));

    int id = row * m_columns + column;
//    assert(id >= 0 && id < m_columns * m_rows && "ID is out of bounds");

    if (id >= 0 && id < m_columns * m_rows) {
        return m_graph->getNodes().at(static_cast<unsigned long>(id));
    } else {
        return new MapNode();
    }
}
