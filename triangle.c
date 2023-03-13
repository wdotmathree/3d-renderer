#include "triangle.h"

void drawTriangle(SDL_Renderer *renderer, const vec2 *p1, const vec2 *p2, const vec2 *p3) {
	SDL_RenderDrawLine(renderer, p1->x, p1->y, p2->x, p2->y);
	SDL_RenderDrawLine(renderer, p2->x, p2->y, p3->x, p3->y);
	SDL_RenderDrawLine(renderer, p1->x, p1->y, p3->x, p3->y);
}

void fillTriangle(SDL_Renderer *renderer, const vec2 *p1, const vec2 *p2, const vec2 *p3) {
	vec2 left, mid, right;
	if (p1->x < p2->x) {
		if (p1->x < p3->x) {
			left = *p1;
			if (p2->x < p3->x) {
				mid = *p2;
				right = *p3;
			} else {
				mid = *p3;
				right = *p2;
			}
		} else {
			left = *p3;
			mid = *p1;
			right = *p2;
		}
	} else {
		if (p2->x < p3->x) {
			left = *p2;
			if (p1->x < p3->x) {
				mid = *p1;
				right = *p3;
			} else {
				mid = *p3;
				right = *p1;
			}
		} else {
			left = *p3;
			mid = *p2;
			right = *p1;
		}
	}
	float m1 = (left.y - right.y) / (left.x - right.x);
	float m2 = (left.y - mid.y) / (left.x - mid.x);
	float m3 = (mid.y - right.y) / (mid.x - right.x);
	float b1 = left.y - m1 * left.x;
	float b2 = left.y - m2 * left.x;
	float b3 = mid.y - m3 * mid.x;
	float top = fminf(fminf(left.y, mid.y), right.y);
	float bottom = fmaxf(fmaxf(left.y, mid.y), right.y);
	for (int x = ceilf(left.x); x < mid.x; x++) {
		float y1 = m1 * x + b1;
		float y2 = m2 * x + b2;
		y1 = fminf(fmaxf(y1, top), bottom);
		y2 = fminf(fmaxf(y2, top), bottom);
		SDL_RenderDrawLine(renderer, x, y1, x, y2);
	}
	for (int x = ceilf(mid.x); x < right.x; x++) {
		float y1 = m1 * x + b1;
		float y2 = m3 * x + b3;
		y1 = fminf(fmaxf(y1, top), bottom);
		y2 = fminf(fmaxf(y2, top), bottom);
		SDL_RenderDrawLine(renderer, x, y1, x, y2);
	}
}
