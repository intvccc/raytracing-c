#ifndef _BMP_H_
#define _BMP_H_

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "options.h"
#include "misc_math.h"

#define HEADER_SIZE				0x36
#define INFO_HEADER_SIZE		40

#define PLANES					1
#define BPP						24
#define	COMPRESSION				0
#define XPPM					0
#define YPPM					0
#define COLOR_USED				16777216
#define IMPORTANT_COLORS		0

#define SIGNATURE_OFFSET		0x00
#define FILE_SIZE_OFFSET		0x02
#define DATA_OFFSET_OFFSET		0x0A
#define SIZE_OFFSET				0x0E
#define WIDTH_OFFSET			0x12
#define HEIGHT_OFFSET			0x16
#define PLANES_OFFSET			0x1A
#define BPP_OFFSET				0x1C
#define COMPRESSION_OFFSET		0x1E
#define IMAGE_SIZE_OFFSET		0x22
#define XPPM_OFFSET				0x26
#define YPPM_OFFSET				0x2A
#define COLOR_USED_OFFSET		0x2E
#define IMPORTANT_COLORS_OFFSET	0x32
#define COLOR_TABLE_OFFSET		0x36
#define IMAGE_DATA_OFFSET		HEADER_SIZE

bool bmp_write(v3f* image_buffer, size_t width, size_t height, const char* filename);

static inline float clampu32(uint32_t t, uint32_t domain_min, uint32_t domain_max)
{
	const uint32_t temp = t < domain_min ? domain_min : t;
	return temp > domain_max ? domain_max : temp;
}

#endif
