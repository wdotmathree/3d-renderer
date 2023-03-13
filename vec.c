#include "vec.h"

float vec3_dot(const vec3 *a, const vec3 *b) {
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

void vec3_cross(vec3 *p, const vec3 *a, const vec3 *b) {
    p->x = a->y * b->z - a->z * b->y;
    p->y = a->z * b->x - a->x * b->z;
    p->z = a->x * b->y - a->y * b->x;
}

void vec3_normalize(vec3 *p) {
    float len = sqrtf(p->x * p->x + p->y * p->y + p->z * p->z);
    p->x /= len;
    p->y /= len;
    p->z /= len;
}
