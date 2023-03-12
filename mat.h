#pragma once
#ifndef MAT_H
#define MAT_H

#include "vec.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>

/**
 * @brief Get the identity matrix
 * @param m The matrix to set to the identity matrix
 */
void mat4x4_identity(float [4][4]);

/**
 * @brief Transpose a matrix
 * @param m The matrix to transpose
 */
void mat4x4_transpose(float[4][4]);

/**
 * @brief Get the determinant of a 3x3 matrix
 * @param m The matrix to get the determinant of
 * @return The determinant of the matrix
 */
float mat3x3_det(const float[3][3]);

/**
 * @brief Get the determinant of a matrix
 * @param m The matrix to get the determinant of
 * @return The determinant of the matrix
 */
float mat4x4_det(const float[4][4]);

/**
 * @brief Invert a matrix
 * @param inv The matrix to store the inverse in
 * @param m The matrix to invert
 * @return 0 if the matrix is singular, 1 otherwise
 */
int mat4x4_invert(float[4][4], const float[4][4]);

/**
 * @brief Multiply two matrices
 * @param out The matrix to store the result in
 * @param a The first matrix
 * @param b The second matrix
 */
void mat4x4_mul(float[4][4], const float[4][4], const float[4][4]);

/**
 * @brief Multiply a matrix by a vector
 * @param out The vector to store the result in
 * @param m The matrix
 * @param v The vector
 */
void mat4x4_mul_vec4(vec4 *, const float[4][4], const vec4 *);

#endif
