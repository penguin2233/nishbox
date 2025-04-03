#ifndef __NB_MATH_H__
#define __NB_MATH_H__

#include <nb_pre.h>
#include <nb_macro.h>

/* External library */
#ifdef NB_EXPOSE_MATH
#include <GL/gl.h>
#endif

/* NishBox */

/* Standard */

#ifdef NB_EXPOSE_MATH
typedef GLfloat* nb_vector_t;

#define NB_VECTOR_COPY(from, to) \
	to[0] = from[0]; \
	to[1] = from[1]; \
	to[2] = from[2]
#else
typedef void* nb_vector_t;
#endif

float	    nb_log2(float x);
nb_vector_t nb_calculate_normal(nb_vector_t v0, nb_vector_t v1, nb_vector_t v2);

#endif
