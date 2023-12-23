/**
 * Returns a vector of points in CCW order representing the convex hull of the 
 * Minkowski sum of two convex polygons. The vertices of each polygon must be given 
 * in CCW order. The sum will not contain collinear points as long as A and B do not 
 * contain collinear points. The result will be empty iff A is empty or B is empty. 
 * 
 * Will work with line segments (2 points) and single points as well. 
 * O(n + m), where n and m are the number of vertices of A and B. 
*/
#pragma once
#include "Point.h"
#include <vector>
#include <algorithm>
using std::vector;

vector<Point> minkowski(vector<Point> &A, vector<Point> &B) {
    int n = A.size();
    int m = B.size();
    if (n == 0 || m == 0) return {};

    // Find the index of the min point in each polygon
    int mn_a, mn_b;
    mn_a = mn_b = 0;
    for (int i = 1; i < (int)A.size(); i++) {
        if (A[i] < A[mn_a]) mn_a = i;
    }
    for (int i = 1; i < (int)B.size(); i++) {
        if (B[i] < B[mn_b]) mn_b = i;
    }

    vector<Point> ans;
    int i = mn_a;
    int j = mn_b;
    do {
        ans.push_back(A[i] + B[j]);
        int ii = (i + 1) % n;
        int jj = (j + 1) % m;

        // Consider edges a[i] -> a[ii] and b[j] -> b[jj]
        // Advance the pointer that takes on the smaller angle
        long long c = (A[ii] - A[i]).cross(B[jj] - B[j]);
        if (c >= 0) {
            i = ii;
        }
        if (c <= 0) {
            j = jj;
        }
    } while(i != mn_a || j != mn_b);
    return ans;
}


