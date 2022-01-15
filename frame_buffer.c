#include "frame_buffer.h"

int frame_buffer_init(frame_buffer_type* fb, size_t pixel_count)
{
	//if ((fb->memory = (v3f*) malloc(pixel_count * sizeof(v3f))) == NULL) {
	if ((fb->memory = (v3f*) calloc(pixel_count, sizeof(v3f))) == NULL) {
		fprintf(stderr, "Could not create frame buffer.\n");
		return false;
	}
	fb->size = pixel_count;
	return true;
}

void frame_buffer_destory(frame_buffer_type* fb)
{
	free(fb->memory);
}




