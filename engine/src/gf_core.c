#define GF_EXPOSE_CORE
#define GF_EXPOSE_DRAW
#define GF_EXPOSE_CLIENT

#include <gf_pre.h>

/* External library */
#ifdef _WIN32
#include <winsock.h>
#endif

/* Interface */
#include <gf_core.h>

/* Engine */
#include <gf_client.h>
#include <gf_server.h>
#include <gf_log.h>
#include <gf_version.h>
#include <gf_resource.h>
#include <gf_font.h>

/* Standard */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void gf_engine_begin(void) {
	gf_version_t ver;
#ifdef _WIN32
	WSADATA wsa;
#endif
	gf_log_default = stderr;

	gf_version_get(&ver);
	gf_log_function(NULL, "GoldFish Engine %s", ver.full);
	gf_log_function(NULL, "Build date: %s", ver.date);
	gf_log_function(NULL, "Lua %s", ver.lua);
	gf_log_function(NULL, "zlib %s", ver.zlib);
	gf_log_function(NULL, "Thread model: %s", ver.thread);
	gf_log_function(NULL, "Renderer: %s on %s", ver.driver, ver.backend);
#ifdef _WIN32
	WSAStartup(MAKEWORD(1, 1), &wsa);
	gf_log_function(NULL, "Winsock ready", "");
#endif
	gf_client_begin();
	gf_server_begin();
}

void gf_engine_end(void) {
	gf_server_end();
	gf_client_end();
}

gf_engine_t* gf_engine_create(const char* title, int nogui) {
	gf_engine_t* engine = malloc(sizeof(*engine));
	memset(engine, 0, sizeof(*engine));
	engine->log = stderr;
	if(nogui) {
		gf_log_function(engine, "No GUI mode", "");
		engine->client = NULL;
	} else {
		gf_log_function(engine, "GUI mode", "");
		engine->client = gf_client_create(engine, title);
		if(engine->client == NULL) {
			gf_log_function(engine, "Failed to create client interface", "");
			gf_engine_destroy(engine);
			return NULL;
		}
		gf_log_function(engine, "Switching to graphical console", "");
	}
	engine->server = gf_server_create(engine);

	engine->base = gf_resource_create(engine, "base.pak");
	if(!nogui) {
		engine->client->draw->font = gf_font_create_file(engine->client->draw, "base:/font/default.bdf");
	}
	return engine;
}

/**
 * Writing this so I don't forget
 *
 * 1.  Calls gf_client_step
 * 2.  gf_client_step calls gf_draw_step
 * 3.  gf_draw_step calls gf_draw_platform_step (Platform-dependent)
 * 4.  gf_draw_platform_step processes platform-dependent stuffs (e.g. events)
 * 5.  gf_draw_platform_step calls gf_draw_driver_before
 * 6.  gf_draw_platform_step calls gf_draw_frame
 * 7.  gf_draw_frame draws stuffs
 * 8.  gf_draw_platform_step calls gf_draw_driver_after
 * 9.  gf_draw_platform_step swaps buffers
 * 10. Comes back here
 */
void gf_engine_loop(gf_engine_t* engine) {
	while(1) {
		if(engine->client != NULL) {
			if(gf_client_step(engine->client) != 0) break;
		}
	}
}

void gf_engine_destroy(gf_engine_t* engine) {
	if(engine->server != NULL) gf_server_destroy(engine->server);
	if(engine->client != NULL) gf_client_destroy(engine->client);
	if(engine->base != NULL) gf_resource_destroy(engine->base);
	free(engine);
	gf_log_function(NULL, "Destroyed engine", "");
}
