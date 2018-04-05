#ifndef DZ04_GLOBALS_H
#define DZ04_GLOBALS_H

namespace globals {
    const int TILE_SIZE = 64;
    const int MAX_TERRAIN_TYPES = 4;
    const int SPRITE_SIZE = 32;

    const bool debug = false;
	

    enum entityTypes {
        invalidEntity,
        terrain,
        tile,
        graph,
        character
    };
}

#endif //DZ04_GLOBALS_H
