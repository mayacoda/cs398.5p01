
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
        if (oldTextures.find(type) == oldTextures.end()) {
            oldTextures.insert(std::pair<MapNode::terrainType, unsigned int>(type,
                                                                             loadTexture(determineFileName(type))));
        }

        return oldTextures[type];
    }

    unsigned int getTextureId(TextureMetadata metadata) {
        if (textures.find(metadata) == textures.end()) {
            textures.insert(std::pair<TextureMetadata, unsigned int>(metadata, loadTextureByMeta(metadata)));
        }

        return textures[metadata];
    }

private:
    MapGraphicsHelper() {}

    MapGraphicsHelper(MapGraphicsHelper const &);

    void operator=(MapGraphicsHelper const &);

    std::map<MapNode::terrainType, unsigned int> oldTextures;
    std::map<TextureMetadata, unsigned int>      textures;

    unsigned int loadTextureByMeta(TextureMetadata meta) {
        std::string file = "assets/";
        file += std::to_string(globals::TILE_SIZE);
        file += "/";

        // determine what type of terrain it is
        if (meta.is(TextureMetadata::none)) file += "grass-";
        if (meta.is(TextureMetadata::mountains)) file += "mountains-";
        if (meta.is(TextureMetadata::forest)) file += "forest-";
        if (meta.is(TextureMetadata::water)) file += "water-";

        if (meta.is(TextureMetadata::none)) {
            file += "f";
        } else {
            file += meta.extension;
        }

        file += ".bmp";

        return loadTexture(file.c_str());
    }

    unsigned int loadTexture(const char* fileName) {
        GLuint ID;

        // read in the pixel data
        BITMAPINFO   * info;
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
        std::string str;
        switch (type) {
            case MapNode::water:
                str += "assets/water" + std::to_string(globals::TILE_SIZE) + ".bmp";
                return str.c_str();
            case MapNode::mountain:
                str = "assets/mountains" + std::to_string(globals::TILE_SIZE) + ".bmp";
                return str.c_str();

            case MapNode::forest:
                str = "assets/forest" + std::to_string(globals::TILE_SIZE) + ".bmp";
                return str.c_str();
            case MapNode::none:
            default:
                str = "assets/grass" + std::to_string(globals::TILE_SIZE) + ".bmp";
                std::cout << str << std::endl;
                return str.c_str();
        }
    }
};


#endif //DZ04_MAPHELPER_H
