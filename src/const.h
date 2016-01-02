#pragma once

#define TREXO_FIELD_SIDE (6)

#define TREXO_NUM_FIELDS (TREXO_FIELD_SIDE * TREXO_FIELD_SIDE)

#define TREXO_MAX_CHILDREN (4 * TREXO_FIELD_SIDE * (TREXO_FIELD_SIDE - 1))

#ifndef FALSE
	#define FALSE (0)
	#define TRUE (!FALSE)
#endif

#ifndef bool
#define bool int
#endif

#define TREXO_IMAGE_PATH "./images/default"

#define TREXO_HISTORY_SIZE (1000)

enum trexo_direction{
    TREXO_LEFT = 0,
    TREXO_RIGHT = 1,
    TREXO_UP = 2,
    TREXO_DOWN = 3,
    TREXO_MAX_DIR = TREXO_DOWN,
    TREXO_MIN_DIR = TREXO_LEFT
};