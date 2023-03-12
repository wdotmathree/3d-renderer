#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vec.h"
#include <SDL.h>

/**
 * @brief Draw a triangle on the screen
 * @param renderer The renderer to draw on
 * @param p1 The first point
 * @param p2 The second point
 * @param p3 The third point
 */
void drawTriangle(SDL_Renderer *, const vec2 *, const vec2 *, const vec2 *);
/**
 * @brief Fill a triangle on the screen
 * @param renderer The renderer to draw on
 * @param p1 The first point
 * @param p2 The second point
 * @param p3 The third point
 */
void fillTriangle(SDL_Renderer *, const vec2 *, const vec2 *, const vec2 *);

#endif
