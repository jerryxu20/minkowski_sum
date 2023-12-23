#pragma once
#include "Point.h"

int section(Point p) {
    if (p.x > 0 || (p.x == 0 && p.y > 0)) return 0;
    return 1;
}

// Returns true if a's angle CCW from the negative x axis is less than
// or equal to b's angle CCW from the negative x axis
// Points on the negative y axis are defined to be larger than anything else. 
// Using this comparator to sort will not work correctly for (0, 0)
bool polarcomp(Point a, Point b) {
    if (section(a) != section(b)) return section(a) < section(b);
    return a.cross(b) > 0;
}
