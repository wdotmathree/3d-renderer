#include "transform.h"

void mat4x4_translate(float m[4][4], float x, float y, float z) {
	float tmp[4][4] = {
		{1, 0, 0, x},
		{0, 1, 0, y},
		{0, 0, 1, z},
		{0, 0, 0, 1},
	};
	mat4x4_mul(m, m, tmp);
}

void mat4x4_scale(float m[4][4], float x, float y, float z) {
	float tmp[4][4] = {
		{x, 0, 0, 0},
		{0, y, 0, 0},
		{0, 0, z, 0},
		{0, 0, 0, 1},
	};
	mat4x4_mul(m, m, tmp);
}

void mat4x4_rotate(float m[4][4], float x, float y, float z) {
	x = x * M_PI / 180;
	y = y * M_PI / 180;
	z = z * M_PI / 180;
	// wtf
	float tmp[4][4] = {
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1},
	};
	if (x != 0) {
		float c = cos(x);
		float s = sin(x);
		float tmp2[4][4] = {
			{c, 0, s, 0},
			{0, 1, 0, 0},
			{-s, 0, c, 0},
			{0, 0, 0, 1},
		};
		mat4x4_mul(tmp, tmp, tmp2);
	}
	if (y != 0) {
		float c = cos(y);
		float s = sin(y);
		float tmp2[4][4] = {
			{c, -s, 0, 0},
			{s, c, 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1},
		};
		mat4x4_mul(tmp, tmp, tmp2);
	}
	if (z != 0) {
		float c = cos(z);
		float s = sin(z);
		float tmp2[4][4] = {
			{1, 0, 0, 0},
			{0, c, -s, 0},
			{0, s, c, 0},
			{0, 0, 0, 1},
		};
		mat4x4_mul(tmp, tmp, tmp2);
	}
	mat4x4_mul(m, m, tmp);
}

void mat4x4_perspective(float m[4][4], float fov, float a, float znear, float zfar) {
	float f = 1 / tan(fov / 2 / 180 * M_PI);
	
	float q = zfar / (zfar - znear);
	memset(m, 0, sizeof(float[4][4]));
	m[0][0] = a * f;
	m[1][1] = f;
	m[2][2] = q;
	m[2][3] = -znear * q;
}

void vec4_toscreen(vec2 *out, const vec4 *v, int w, int h) {
	out->x = (v->x / v->z + 1) * w / 2;
	out->y = (v->y / v->z + 1) * h / 2;
}
