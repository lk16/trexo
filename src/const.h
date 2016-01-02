#pragma once

#define TREXO_FIELD_SIDE (10)

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