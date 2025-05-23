/**
 * @file gf_opengl.h
 * @~english
 * @brief OpenGL headers
 * @note User should not include this, this header is used internally
 */

#ifndef __GF_OPENGL_H__
#define __GF_OPENGL_H__

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#if defined(USE_GLX)
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <GL/glx.h>
#elif defined(USE_WGL)
/* Should require nothing... for now? */
#elif defined(USE_GLFW)
#include <GLFW/glfw3.h>
#endif

#endif
