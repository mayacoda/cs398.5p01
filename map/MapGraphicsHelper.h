
#ifndef DZ04_MAPHELPER_H
#define DZ04_MAPHELPER_H


#include <map>
#include <sstream>
#include "MapNode.h"
#include "../graphics/bmp-mac.h"


#ifdef _WIN32
#include <GL\glut.h>
#elif __APPLE__
#include <GLUT/glut.h>
#endif

class MapGraphicsHelper {
public:
    static MapGraphicsHelper &getInstance() {
        static MapGraphicsHelper instance;
        return instance;
    }

    unsigned int getTextureId(MapNode::terrainType type) {
        if (textures.find(type) == textures.end()) {
            textures.insert(std::pair<MapNode::terrainType, unsigned int>(type, loadTexture(determineFileName(type))));
        }

        return textures[type];
    }

private:
    MapGraphicsHelper() {}

    MapGraphicsHelper(MapGraphicsHelper const &);

    void operator=(MapGraphicsHelper const &);

    std::map<MapNode::terrainType, unsigned int> textures;

    unsigned int loadTexture(const char* fileName) {
        GLuint ID;

        // read in the pixel data
        BITMAPINFO* info;
        unsigned char* pixels = ReadBitmap(fileName, &info);

        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);

        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth,
                     info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE,
                     pixels);

        return ID;
    }

    const char* determineFileName(MapNode::terrainType type) const {
        std::stringstream format;
        format << globals::TILE_SIZE;

        switch (type) {
            case MapNode::water: {
                return ("assets/water" + format.str() + ".bmp").c_str();
            }
            case MapNode::mountain:
                return ("assets/mountains" + format.str() + ".bmp").c_str();
            case MapNode::forest:
                return ("assets/forest" + format.str() + ".bmp").c_str();
            case MapNode::none:
            default:
                return ("assets/grass" + format.str() + ".bmp").c_str();
        }
    }
};


#endif //DZ04_MAPHELPER_H
