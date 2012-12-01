/*
 * CTile.h
 *
 *  Created on: 01.12.2012
 *      Author: Armend
 */

#ifndef _CTILE_H_
    #define _CTILE_H_

#include "Define.h"

enum {
    TILE_TYPE_NONE = 0,

    TILE_TYPE_GROUND,
    TILE_TYPE_BLOCK
};

class CTile {
    public:
        int     TileID; 	// img ID
        int     TypeID; 	// type like block, ground etc

    public:
        CTile();
};

#endif
