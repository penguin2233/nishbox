/**
 * Log
 *
 * Provides useful function/macro for logging.
 * Uses the graphical console if possible.
 */

#ifndef __GF_LOG_H__
#define __GF_LOG_H__

#include <gf_pre.h>
#include <gf_macro.h>

/* Type */

/* Engine */
#include <gf_type/core.h>

/* Standard */

#define gf_function_log(engine, fmt, ...) gf_log(engine, "%6d %24s: " fmt "\n", __LINE__, __FUNCTION_NAME__, __VA_ARGS__)

GF_EXPORT void gf_log(gf_engine_t* engine, const char* fmt, ...);

#endif
