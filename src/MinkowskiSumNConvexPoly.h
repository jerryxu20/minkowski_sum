/**
 * Computes the convex hull of the minkowski sum of n convex polygons. 
 * Returns it as a vector of points in CCW order. The vertices of all polygons 
 * should be given in CCW order. The result will be empty iff any polygon is empty. 
 * If there is only one polygon, the return is that polygon. 
 * 
 * Will work with line segments (2 points) and single points as well. The result may
 * contain collinear points. 
 * O(Nlog(N)), where N is the total number of points
*/
#pragma once
#include "Point.h"
#include "PolarComp.h"
#include <vector>
#include <algorithm>
using std::vector;
using std::min;

vector<Point> minkowski(vector<vector<Point>> &poly) {
    vector<Point> offsets;
    Point cur(0, 0);
    
    // Compute the offsets for each polygon
    for (auto &pts: poly) {
        int n = pts.size();
        if (n == 0) return {};

        Point mn = pts[0];
        for (int i = 0; i < n; i++) {
            mn = min(mn, pts[i]);
            Point delta = pts[(i + 1) % n] - pts[i];
            
            // Ignore duplicate points
            if (delta.x == 0 && delta.y == 0) continue;

            offsets.push_back(delta);
        }
        // Add min point of polygon to starting point
        cur = cur + mn;
    }

    vector<Point> ans;

    // Sort offsets by angle
    sort(offsets.begin(), offsets.end(), polarcomp);

    // Compute the convex hull of the sum
    for (auto &offset: offsets) {
        ans.push_back(cur);
        cur = cur + offset;
    }

    // All polygons were size 1
    if (ans.empty()) return {cur};
    
    return ans;
}