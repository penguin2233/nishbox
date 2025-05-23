#define GF_EXPOSE_DRAW_PLATFORM
#define GF_EXPOSE_DRAW
#define GF_EXPOSE_INPUT

#include <gf_pre.h>

/* External library */
#include <gf_opengl.h>

/* Interface */
#include <gf_draw_platform.h>

/* Engine */
#include <gf_draw_driver.h>
#include <gf_log.h>
#include <gf_draw.h>
#include <gf_input.h>

/* Standard */
#include <string.h>
#include <stdlib.h>

void gf_draw_platform_begin(void) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
}

void gf_draw_platform_end(void) {}

void gf_glfw_size(GLFWwindow* window, int w, int h) {
	gf_draw_t* draw = (gf_draw_t*)glfwGetWindowUserPointer(window);
	draw->width	= w;
	draw->height	= h;
	glfwSetWindowSize(window, w, h);
	gf_draw_reshape(draw);
}

void gf_glfw_button(GLFWwindow* window, int button, int action, int mods) {
	gf_draw_t* draw = (gf_draw_t*)glfwGetWindowUserPointer(window);
	if(draw->input != NULL) {
		if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) draw->input->mouse_flag |= GF_INPUT_MOUSE_LEFT_MASK;
		if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) draw->input->mouse_flag ^= GF_INPUT_MOUSE_LEFT_MASK;

		if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) draw->input->mouse_flag |= GF_INPUT_MOUSE_RIGHT_MASK;
		if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) draw->input->mouse_flag ^= GF_INPUT_MOUSE_RIGHT_MASK;

		if(button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS) draw->input->mouse_flag |= GF_INPUT_MOUSE_MIDDLE_MASK;
		if(button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE) draw->input->mouse_flag ^= GF_INPUT_MOUSE_MIDDLE_MASK;
	}
}

void gf_glfw_cursor(GLFWwindow* window, double x, double y) {
	gf_draw_t* draw = (gf_draw_t*)glfwGetWindowUserPointer(window);
	if(draw->input != NULL) {
		draw->input->mouse_x = x;
		draw->input->mouse_y = y;
	}
}

int gf_draw_platform_has_extension(gf_draw_t* draw, const char* query) {
	const char* ext = NULL;
	const char* ptr;
	const int   len = strlen(query);

	glfwMakeContextCurrent(draw->platform->window);

	return glfwExtensionSupported(query);
}

int gf_draw_platform_step(gf_draw_t* draw) {
	int ret = 0;
	int w, h;
	glfwMakeContextCurrent(draw->platform->window);
	draw->close = glfwWindowShouldClose(draw->platform->window);
	if(draw->close) glfwSetWindowShouldClose(draw->platform->window, GLFW_FALSE);
	glfwPollEvents();
	if(ret == 0) {
		gf_draw_driver_before(draw);
		gf_draw_frame(draw);
		gf_draw_driver_after(draw);

		glfwSwapBuffers(draw->platform->window);
	}
	return ret;
}

gf_draw_platform_t* gf_draw_platform_create(gf_engine_t* engine, gf_draw_t* draw) {
	gf_draw_platform_t* platform = malloc(sizeof(*platform));
	memset(platform, 0, sizeof(*platform));
	platform->engine = engine;

	platform->window = glfwCreateWindow(draw->width, draw->height, draw->title, NULL, NULL);
	if(platform->window == NULL) {
		gf_log_function(engine, "Failed to create window", "");
		gf_draw_platform_destroy(platform);
		return NULL;
	}

	glfwSetWindowUserPointer(platform->window, draw);
	glfwSetCursorPosCallback(platform->window, gf_glfw_cursor);
	glfwSetWindowSizeCallback(platform->window, gf_glfw_size);
	glfwSetMouseButtonCallback(platform->window, gf_glfw_button);

	glfwMakeContextCurrent(platform->window);
#ifdef DO_SWAP_INTERVAL
	glfwSwapInterval(1);
#endif
	return platform;
}

void gf_draw_platform_destroy(gf_draw_platform_t* platform) {
	if(platform->window != NULL) {
		glfwDestroyWindow(platform->window);
	}
	gf_log_function(platform->engine, "Destroyed platform-dependent part of drawing driver", "");
	free(platform);
}
