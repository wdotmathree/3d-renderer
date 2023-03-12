#include "mat.h"
#include "transform.h"
#include "triangle.h"
#include <stdio.h>
#include <SDL.h>

int main() {
	// init sdl
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	// make a shape
	vec4 p1 = {0, 0, 2, 1};
	vec4 p2 = {0.5, 0.5, 3, 1};
	vec4 p3 = {0.5, -0.5, 3, 1};
	vec4 p4 = {-0.5, -0.5, 3, 1};
	vec4 p5 = {-0.5, 0.5, 3, 1};
	// make a matrix
	float m[4][4];
	int i = 0;
	SDL_Event e;
	while (1) {
		// get the projection matrix
		mat4x4_perspective(m, 90, 1, 1, 10);
		// rotate
		mat4x4_rotate(m, i++, 0, 0);
		// project the shape
		vec4 p1p, p2p, p3p, p4p, p5p;
		mat4x4_mul_vec4(&p1p, m, &p1);
		mat4x4_mul_vec4(&p2p, m, &p2);
		mat4x4_mul_vec4(&p3p, m, &p3);
		mat4x4_mul_vec4(&p4p, m, &p4);
		mat4x4_mul_vec4(&p5p, m, &p5);
		// convert to screen coordinates
		vec2 p1s, p2s, p3s, p4s, p5s;
		vec4_toscreen(&p1s, &p1p, 500, 500);
		vec4_toscreen(&p2s, &p2p, 500, 500);
		vec4_toscreen(&p3s, &p3p, 500, 500);
		vec4_toscreen(&p4s, &p4p, 500, 500);
		vec4_toscreen(&p5s, &p5p, 500, 500);
		// draw the results
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		drawTriangle(renderer, &p1s, &p2s, &p3s);
		drawTriangle(renderer, &p1s, &p3s, &p4s);
		drawTriangle(renderer, &p1s, &p4s, &p5s);
		drawTriangle(renderer, &p1s, &p5s, &p2s);
		drawTriangle(renderer, &p2s, &p5s, &p4s);
		drawTriangle(renderer, &p2s, &p4s, &p3s);
		SDL_RenderPresent(renderer);
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				break;
			}
		}
		SDL_Delay(10);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
