#include "triangle.h"

void drawTriangle(SDL_Renderer *renderer, const vec2 *p1, const vec2 *p2, const vec2 *p3) {
	SDL_RenderDrawLine(renderer, p1->x, p1->y, p2->x, p2->y);
	SDL_RenderDrawLine(renderer, p2->x, p2->y, p3->x, p3->y);
	SDL_RenderDrawLine(renderer, p1->x, p1->y, p3->x, p3->y);
}

void fillTriangle(SDL_Renderer *renderer, const vec2 *p1, const vec2 *p2, const vec2 *p3) {
	vec2 top, mid, bot;

	if (p1->y < p2->y)
		top = *p1;
	else
		top = *p2;
	if (p3->y < top.y) {
		mid = top;
		top = *p3;
	} else {
		mid = *p3;
	}
	bot.x = p1->x + p2->x + p3->x - top.x - mid.x;
	bot.y = p1->y + p2->y + p3->y - top.y - mid.y;

	float m1 = (mid.x - top.x) / (mid.y - top.y);
	float m2 = (bot.x - top.x) / (bot.y - top.y);
	float m3 = (bot.x - mid.x) / (bot.y - mid.y);
	float b1 = top.x - m1 * top.y;
	float b2 = top.x - m2 * top.y;
	float b3 = mid.x - m3 * mid.y;

	for (int y = top.y; y <= mid.y; y++) {
		int x1 = m1 * y + b1;
		int x2 = m2 * y + b2;
		SDL_RenderDrawLine(renderer, x1, y, x2, y);
	}
	for (int y = mid.y; y <= bot.y; y++) {
		int x1 = m2 * y + b2;
		int x2 = m3 * y + b3;
		SDL_RenderDrawLine(renderer, x1, y, x2, y);
	}
}
