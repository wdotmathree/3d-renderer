#include "mat.h"
#include "transform.h"
#include "triangle.h"
#include <SDL.h>
#include <stdio.h>

// void sort(vec4 *arr, int start, int end) {
// 	// quicksort in decending order
// 	if (start >= end)
// 		return;
// 	vec4 temp[3];
// 	float pivot = arr[start].z;
// 	int i = start + 3;
// 	int j = end;
// 	while (i <= j) {
// 		while (i <= end && arr[i].z >= pivot)
// 			i += 3;
// 		while (j > start && arr[j].z < pivot)
// 			j -= 3;
// 		if (i < j) {
// 			vec4 temp[3];
// 			temp[0] = arr[i];
// 			temp[1] = arr[i + 1];
// 			temp[2] = arr[i + 2];
// 			arr[i] = arr[j];
// 			arr[i + 1] = arr[j + 1];
// 			arr[i + 2] = arr[j + 2];
// 			arr[j] = temp[0];
// 			arr[j + 1] = temp[1];
// 			arr[j + 2] = temp[2];
// 		}
// 	}
// 	temp[0] = arr[start];
// 	temp[1] = arr[start + 1];
// 	temp[2] = arr[start + 2];
// 	arr[start] = arr[j];
// 	arr[start + 1] = arr[j + 1];
// 	arr[start + 2] = arr[j + 2];
// 	arr[j] = temp[0];
// 	arr[j + 1] = temp[1];
// 	arr[j + 2] = temp[2];
// 	sort(arr, start, j - 3);
// 	sort(arr, j + 3, end);
// }

void sort(vec4 *arr, int len) {
	len *= 3;
	for (int i = 0; i < len; i += 3) {
		for (int j = i; j > 0; j -= 3) {
			if (arr[j].z > arr[j - 3].z) {
				vec4 temp[3];
				temp[0] = arr[j];
				temp[1] = arr[j + 1];
				temp[2] = arr[j + 2];
				arr[j] = arr[j - 3];
				arr[j + 1] = arr[j - 2];
				arr[j + 2] = arr[j - 1];
				arr[j - 3] = temp[0];
				arr[j - 2] = temp[1];
				arr[j - 1] = temp[2];
			}
		}
	}
}

int main() {
	// init sdl
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	// make a shape
	vec4 verticies[576];
	FILE *f = fopen("thing.obj", "r");
	int i = 0;
	while (1) {
		char c;
		fscanf(f, "%c", &c);
		if (c == 'v') {
			fscanf(f, "%f %f %f", &verticies[i].x, &verticies[i].y, &verticies[i].z);
			verticies[i].w = 1;
			i++;
		} else if (c == 'f') {
			fseek(f, -1, SEEK_CUR);
			break;
		}
	}
	// make a list of triangles
	vec4 triangles[1152][3];
	i = 0;
	while (i < 1152) {
		int a, b, c;
		char x;
		fscanf(f, "%c", &x);
		if (x != 'f')
			continue;
		fscanf(f, "%d %d %d", &a, &b, &c);
		triangles[i][0] = verticies[a - 1];
		triangles[i][1] = verticies[b - 1];
		triangles[i][2] = verticies[c - 1];
		i++;
	}
	// make a matrix
	float m[4][4];
	float m2[4][4];
	int t = 0;
	SDL_Event e;
	unsigned long long prevtime = SDL_GetPerformanceCounter();
	int j = 0;
	while (1) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		// rotate the shape
		mat4x4_rotate(m2, 0, t / 2, 0);
		// rotate the shape
		mat4x4_rotate(m, -40, 0, 0);
		mat4x4_mul(m2, m2, m);
		t++;
		// mat4x4_scale(m, 0.5, 0.5, 0.5);
		// mat4x4_mul(m2, m, m2);
		// translate the shape
		mat4x4_translate(m, 0, 0, 4);
		mat4x4_mul(m2, m, m2);
		// get the projection matrix
		mat4x4_perspective(m, 90, 1, 1, 10);
		// multiply the matrices
		mat4x4_mul(m, m, m2);
		// apply the transformations
		vec4 newtriangles[1152][3];
		for (int i = 0; i < 1152; i++) {
			mat4x4_mul_vec4(&newtriangles[i][0], m, &triangles[i][0]);
			mat4x4_mul_vec4(&newtriangles[i][1], m, &triangles[i][1]);
			mat4x4_mul_vec4(&newtriangles[i][2], m, &triangles[i][2]);
		}
		// sort the triangles
		// sort(newtriangles, 0, 1149);
		sort(newtriangles, 1152);
		for (int i = 0; i < 1152; i++) {
			vec4 p1, p2, p3;
			p1 = newtriangles[i][0];
			p2 = newtriangles[i][1];
			p3 = newtriangles[i][2];
			// see if the triangle is facing the camera
			vec3 vis, n, v1, v2;
			v1 = (vec3){p3.x - p1.x, p3.y - p1.y, p3.z - p1.z};
			v2 = (vec3){p2.x - p1.x, p2.y - p1.y, p2.z - p1.z};
			vec3_cross(&n, &v1, &v2);
			vec3_normalize(&n);
			vis = (vec3){p1.x, p1.y, p1.z};
			vec3_normalize(&vis);
			if (vec3_dot(&n, &vis) <= 0)
				continue;
			vec2 p1s, p2s, p3s;
			vec4_toscreen(&p1s, &p1, 1000, 1000);
			vec4_toscreen(&p2s, &p2, 1000, 1000);
			vec4_toscreen(&p3s, &p3, 1000, 1000);
			// calculate lighting
			vec3 light = (vec3){2, 2, -2};
			vec3_normalize(&light);
			float intensity = -vec3_dot(&n, &light);
			if (intensity < 0)
				intensity = 0;
			SDL_SetRenderDrawColor(renderer, 255 * intensity, 255 * intensity, 255 * intensity, 255);
			fillTriangle(renderer, &p1s, &p2s, &p3s);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			// SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			drawTriangle(renderer, &p1s, &p2s, &p3s);
		}
		SDL_RenderPresent(renderer);
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				break;
			}
		}
		if (j == 100) {
			printf("%lffps\n", 100 * SDL_GetPerformanceFrequency() / (float)(SDL_GetPerformanceCounter() - prevtime));
			prevtime = SDL_GetPerformanceCounter();
			j = 0;
		} else
			j++;
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
