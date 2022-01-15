#ifndef _OPTIONS_H_
#define _OPTIONS_H_

#define DEBUG 1
#if DEBUG
#include <stdio.h>
#define DEBUG_PRINTF(...) printf(__VA_ARGS__)
#else
#define DEBUG_PRINTF(...)
#endif

#define BITMAP_WIDTH 		7680
#define BITMAP_HEIGHT 		4320
#define BITMAP_PIXEL_COUNT	(BITMAP_WIDTH*BITMAP_HEIGHT)
#define BITMAP_FILE_NAME 	"out.bmp"

#define PIXEL_SIZE 0.00001f
#define FOCAL_LENGTH 0.04f

#define MAX_REFLECT_COUNT 10

#endif	// _OPTIONS_H_
