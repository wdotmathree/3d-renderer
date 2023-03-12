#include "mat.h"

void mat4x4_identity(float m[4][4]) {
	memset(m, 0, sizeof(float[4][4]));
	m[0][0] = 1;
	m[1][1] = 1;
	m[2][2] = 1;
	m[3][3] = 1;
}

void mat4x4_transpose(float m[4][4]) {
	float t;
	for (int i = 0; i < 4; i++) {
		for (int j = i + 1; j < 4; j++) {
			t = m[i][j];
			m[i][j] = m[j][i];
			m[j][i] = t;
		}
	}
}

float mat3x3_det(const float m[3][3]) {
	float det = m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]);
	det -= m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]);
	det += m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
	return det;
}

float mat4x4_det(const float m[4][4]) {
	float det = m[0][0] * mat3x3_det((float[3][3]){
		{m[1][1], m[1][2], m[1][3]},
		{m[2][1], m[2][2], m[2][3]},
		{m[3][1], m[3][2], m[3][3]},
	});
	det -= m[0][1] * mat3x3_det((float[3][3]){
		{m[1][0], m[1][2], m[1][3]},
		{m[2][0], m[2][2], m[2][3]},
		{m[3][0], m[3][2], m[3][3]},
	});
	det += m[0][2] * mat3x3_det((float[3][3]){
		{m[1][0], m[1][1], m[1][3]},
		{m[2][0], m[2][1], m[2][3]},
		{m[3][0], m[3][1], m[3][3]},
	});
	det -= m[0][3] * mat3x3_det((float[3][3]){
		{m[1][0], m[1][1], m[1][2]},
		{m[2][0], m[2][1], m[2][2]},
		{m[3][0], m[3][1], m[3][2]},
	});
	return det;
}

int mat4x4_invert(float inv[4][4], const float m[4][4]) {
	float det = mat4x4_det(m);
	if (det == 0)
		return 0;
	float tmp[3][3];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 3; k++) {
				for (int l = 0; l < 3; l++) {
					tmp[k][l] = m[(k < i ? k : k + 1)][(l < j ? l : l + 1)];
				}
			}
			inv[j][i] = mat3x3_det(tmp) * ((i + j) % 2 ? -1 : 1) / det;
		}
	}
	mat4x4_transpose(inv);
	return 1;
}

void mat4x4_mul(float out[4][4], const float a[4][4], const float b[4][4]) {
	float tmp[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			tmp[i][j] = 0;
			for (int k = 0; k < 4; k++) {
				tmp[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			out[i][j] = tmp[i][j];
		}
	}
}

void mat4x4_mul_vec4(vec4 *out, const float m[4][4], const vec4 *v) {
	float tmp[4] = {0};
	float tmpv[4] = {v->x, v->y, v->z, v->w};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			tmp[i] += m[i][j] * tmpv[j];
		}
	}
	out->x = tmp[0];
	out->y = tmp[1];
	out->z = tmp[2];
	out->w = tmp[3];
}
