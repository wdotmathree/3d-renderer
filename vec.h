#pragma once
#ifndef VEC_H
#define VEC_H

#include <math.h>

typedef struct {
	float x;
	float y;
} vec2;

typedef struct {
	float x;
	float y;
	float z;
} vec3;

typedef struct {
	float x;
	float y;
	float z;
	float w;
} vec4;

float vec3_dot(const vec3 *a, const vec3 *b);
void vec3_cross(vec3 *p, const vec3 *a, const vec3 *b);
void vec3_normalize(vec3 *p);

#endif
