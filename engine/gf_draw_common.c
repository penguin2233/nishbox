#define GF_EXPOSE_DRAW

#include <gf_pre.h>

/* External library */

/* Interface */
#include <gf_draw.h>

/* Engine */
#include <gf_core.h>
#include <gf_log.h>
#include <gf_draw_platform.h>
#include <gf_draw_driver.h>
#include <gf_graphic.h>

/* Standard */
#include <stdlib.h>
#include <string.h>
#include <math.h>

void gf_draw_begin(void) { gf_draw_platform_begin(); }

void gf_draw_end(void) { gf_draw_platform_end(); }

gf_draw_t* gf_draw_create(gf_engine_t* engine, const char* title) {
	gf_draw_t* draw = malloc(sizeof(*draw));
	memset(draw, 0, sizeof(*draw));
	draw->x	      = 0;
	draw->y	      = 0;
	draw->width   = 640;
	draw->height  = 480;
	draw->running = 0;
	strcpy(draw->title, title);
	gf_draw_platform_create(draw);
	if(draw->platform != NULL) {
		gf_function_log(NULL, "Created drawing interface successfully", "");
		gf_draw_driver_init(draw);
		gf_draw_reshape(draw);
		draw->running = 1;

		draw->light[0] = 10.0;
		draw->light[1] = 10.0;
		draw->light[2] = 0.0;
		draw->light[3] = 1.0;

		draw->camera[0] = 0;
		draw->camera[1] = 10;
		draw->camera[2] = 0;

		draw->lookat[0] = 0;
		draw->lookat[1] = 0;
		draw->lookat[2] = 0;
	}
	return draw;
}

void gf_draw_reshape(gf_draw_t* draw) { gf_draw_driver_reshape(draw); }

/* Runs every frame */
void gf_draw_frame(gf_draw_t* draw) {
	if(draw->draw != NULL) draw->draw(draw);
}

void gf_draw_set_draw(gf_draw_t* draw, void (*func)(gf_draw_t*)) { draw->draw = func; }

int gf_draw_step(gf_draw_t* draw) {
	int ret = gf_draw_platform_step(draw);
	if(ret != 0) return ret;
	draw->close = 0;

	return 0;
}

void gf_draw_destroy(gf_draw_t* draw) {
	int i;
	if(draw->running) {
		gf_draw_driver_destroy(draw);
	}
	gf_draw_platform_destroy(draw);
	gf_function_log(NULL, "Destroyed drawing interface", "");
}
