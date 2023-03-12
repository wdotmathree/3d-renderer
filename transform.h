#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "mat.h"
#include "vec.h"
#include <math.h>
#include <string.h>

/**
 * @brief Create a translation matrix
 * @param m The matrix to store the translation in
 * @param x The x translation
 * @param y The y translation
 * @param z The z translation
 */
void mat4x4_translate(float[4][4], float, float, float);

/**
 * @brief Create a scaling matrix
 * @param m The matrix to store the scaling in
 * @param x The x scaling
 * @param y The y scaling
 * @param z The z scaling
 */
void mat4x4_scale(float[4][4], float, float, float);

/**
 * @brief Create a rotation matrix
 * @param m The matrix to store the rotation in
 * @param x The amount to rotate about the x-axis
 * @param y The amount to rotate about the y-axis
 * @param z The amount to rotate about the z-axis
 */
void mat4x4_rotate(float[4][4], float, float, float);

/**
 * @brief Create a perspective projection matrix
 * @param m The matrix to store the projection in
 * @param fov The field of view
 * @param a The aspect ratio
 * @param znear The distance to the near clipping plane
 * @param zfar The distance to the far clipping plane
 */
void mat4x4_perspective(float [4][4], float, float, float, float);

/**
 * @brief Convert a vector from homogeneous coordinates to screen coordinates
 * @param out The vector to store the result in
 * @param v The vector to convert
 * @param w The width of the screen
 * @param h The height of the screen
 */
void vec4_toscreen(vec2 *, const vec4 *, int, int);

#endif
