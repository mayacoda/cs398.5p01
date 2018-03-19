//
// Created by Maja Nedeljkovic on 3/17/18.
//

#ifndef DZ04_GLOBALS_H
#define DZ04_GLOBALS_H

namespace globals {
    const int TILE_SIZE = 64;
    const int MAX_TERRAIN_TYPES = 4;


    const enum entityTypes {
        invalidEntity,
        terrain,
        tile,
        graph,
        character
    };
}

#endif //DZ04_GLOBALS_H
