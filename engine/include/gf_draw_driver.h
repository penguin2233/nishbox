/**
 * Renderer driver (e.g. OpenGL)
 *
 * Handles driver-specific parts, like lighting.
 */

#ifndef __GF_DRAW_DRIVER_H__
#define __GF_DRAW_DRIVER_H__

#include <gf_pre.h>
#include <gf_macro.h>

/* Type */
#include <gf_type/draw_driver.h>

/* Engine */
#include <gf_type/draw.h>
#include <gf_type/texture.h>
#include <gf_type/graphic.h>

/* Standard */

GF_EXPORT void gf_draw_driver_init(gf_draw_t* draw);
GF_EXPORT void gf_draw_driver_destroy(gf_draw_t* draw);
GF_EXPORT int  gf_draw_driver_has_extension(gf_draw_t* draw, const char* query);
GF_EXPORT void gf_draw_driver_reshape(gf_draw_t* draw);

GF_EXPORT gf_draw_driver_texture_t* gf_draw_driver_register_texture(gf_draw_t* draw, int width, int height, int* iwidth, int* iheight, unsigned char* data);
GF_EXPORT void			    gf_draw_driver_destroy_texture(gf_draw_driver_texture_t* texture);

GF_EXPORT void gf_draw_driver_begin_texture_2d(gf_draw_t* draw, gf_texture_t* texture);
GF_EXPORT void gf_draw_driver_end_texture_2d(gf_draw_t* draw);

GF_EXPORT void gf_draw_driver_set_color(gf_draw_t* draw, gf_color_t color);

GF_EXPORT void gf_draw_driver_before(gf_draw_t* draw);
GF_EXPORT void gf_draw_driver_after(gf_draw_t* draw);

#endif
