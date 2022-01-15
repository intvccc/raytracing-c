#include "bmp.h"

bool bmp_write(v3f* image_buffer, size_t width, size_t height, const char* filename)
{
	FILE* bmp_file = fopen(filename, "wb");
	const size_t pixel_count = width * height;
	const size_t image_block_size = 3 * pixel_count;
	
	if (bmp_file == NULL) {
		fprintf(stderr, "ERROR: Could not create bmp file.\n");
		return false;
	}
	
	uint8_t* image = (uint8_t*) malloc(image_block_size * sizeof(uint8_t));
	if (image == NULL) {
		fprintf(stderr, "ERROR: Could not allocate memory for image block.\n");
		free(image);
		fclose(bmp_file);
		return false;
	}
	
	for (size_t i = 0; i < pixel_count; ++i) {
		uint32_t color_r_temp = (uint32_t)(image_buffer[i].x * 255.0f);
		uint8_t color_r = (uint8_t) clampu32(color_r_temp, 0, 255);
		uint32_t color_g_temp = (uint32_t)(image_buffer[i].y * 255.0f);
		uint8_t color_g = (uint8_t) clampu32(color_g_temp, 0, 255);
		uint32_t color_b_temp = (uint32_t)(image_buffer[i].z * 255.0f);
		uint8_t color_b = (uint8_t) clampu32(color_b_temp, 0, 255);
		image[i*3] = color_b;
		image[i*3+1] = color_g;
		image[i*3+2] = color_r;
	}
	
	fseek(bmp_file, HEADER_SIZE, SEEK_SET);
	if (fwrite(image, sizeof(uint8_t), image_block_size, bmp_file) != image_block_size) {
		fprintf(stderr, "ERROR: Could not write image data.\n");
		free(image);
		fclose(bmp_file);
		return false;
	}
	free(image);
	image = NULL;
	
	uint8_t* header = (uint8_t*) calloc(HEADER_SIZE , sizeof(uint8_t));
	if (header == NULL) {
		fprintf(stderr, "ERROR: Could not allocate memory for header.\n");
		fclose(bmp_file);
		return false;
	}
	
	header[0] = 'B';
	header[1] = 'M';
	*(uint32_t*)&header[FILE_SIZE_OFFSET] = image_block_size + HEADER_SIZE;
	*(uint32_t*)&header[DATA_OFFSET_OFFSET] = IMAGE_DATA_OFFSET;
	*(uint32_t*)&header[SIZE_OFFSET] = INFO_HEADER_SIZE;
	*(uint32_t*)&header[WIDTH_OFFSET] = width;
	*(uint32_t*)&header[HEIGHT_OFFSET] = height;
	*(uint16_t*)&header[PLANES_OFFSET] = PLANES;
	*(uint16_t*)&header[BPP_OFFSET] = BPP;
	*(uint32_t*)&header[COMPRESSION_OFFSET] = COMPRESSION;
	*(uint32_t*)&header[XPPM_OFFSET] = XPPM;
	*(uint32_t*)&header[YPPM_OFFSET] = YPPM;
	*(uint32_t*)&header[COLOR_USED_OFFSET] = COLOR_USED;
	*(uint32_t*)&header[IMPORTANT_COLORS_OFFSET] = IMPORTANT_COLORS;
	
	rewind(bmp_file);
	if (fwrite(header, sizeof(uint8_t), HEADER_SIZE, bmp_file) != HEADER_SIZE) {
		fprintf(stderr, "ERROR: Could not write header.\n");
		free(header);
		fclose(bmp_file);
		return false;
	}
	free(header);
		
	fclose(bmp_file);
	return true;
}
