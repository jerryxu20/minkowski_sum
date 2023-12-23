# Minkowski Sum of Convex Polygons
In general the Minkowski sum of two sets of vectors is the set of vectors that result from adding each vector in A to each vector in B. 

When A and B are convex polygons, the Minkowski sum of A and B will be a convex polygon. My implementation will compute the vertices of the resulting convex polygon in CCW order, given the vertices of A and B (also in CCW order) in O(n + m), where n is the number of vertices in A and m is the number of vertices in B. 

To compute the Minkowski sum of multiple convex polygons, we can continually do the Minkowski sum of two convex polygons, but this is slow. My second implementation will compute the convex hull of the Minkowski sum of 2 or more convex polygons in O(Nlog(N)), where N is the total number of vertices of the polygons. 

### How to Use it
Include it or copy the function you want as well as it's dependencies into your file and then call the function with valid arguments. If it is necessary to not have collinear points in the resulting Minkowski sum, and the function does not guarantee this for your input, then take the convex hull of it after. 

The functions are designed to be used like Kactl, but the implementations do not depend on a template or Kactl code. The Point struct is subset of Kactls Point struct, so the functions would work with Kactls Point struct if you change the parameter types. 

### Peculiarities
Not designed with floats in mind and not tested with floats. 

```
vector<Point> minkowski(vector<Point> A, vector<Point> B)
- When inputs are parallel line segments, but they contain collinear points 
a degenerate polygon may be returned.
  - In this case, may take longer than O(n + m) as result can have more than n + m points. 
- Line segments (2 points), single points, and convex polygons with vertices in CCw are all acceptable inputs 
- The result should not contain collinear points as long as the inputs do not contain collinear points and are valid 
```


```
vector<Point> minkowski(vector<vector<Point>> poly)
- If the expected answer is a line segment then a degenerate polygon may be returned.
  - This is the case when inputs consist of only single points and parallel line segments
  - Just take the convex hull of it after 
- The output will likely contain collinear points
    - Again, if this matters, just take the convex hull if it after
- Input polygons may contain collinear points
- Adjacent duplicate points in polygons are ignored
- If any polygon is empty, the result will be empty
- Line segments (2 points), single points, and convex polygons with vertices in CCw are all acceptable inputs 
- When the input is a single convex polygon, that polygon is returned. 
```

### Tests:
There are only two tests because each problem also tests the efficiency and correctness of my implementations. 

My tests are simple stress tests where I randomly generate input and then compare the output of my implemenation with a correct implementation using book code. These tests are designed to run until output differs, so ideally, they would never stop. 

gen.cpp is the generator and correct.cpp is the correct implementation. 

Run this in each test directory. 
```
bash test.sh
```

#### TEST 1: Testing correctness of my Minkowski sum of two convex polygons
Input format: The vertices of two convex polygons in CCW order.
```
n m
ax_1 ay_1
ax_2 ay_2
...
ax_n ay_n
bx_1 by_1
bx_2 by_2
...
bx_m by_m
```
$1 \le n, n \le 10^6$
$-10^9 \le ax_i, ay_i, bx_j, by_j \le 10^9$
No three consecutive vertices will lie on the same line. All numbers are integers.

Output format: The number of vertices of the Minkowski sum $N$ on the first line, then $N$ lines where the ith line is the coordinates of the ith point. Points should be outputted in CCW order with the min point outputted first. The min point is the leftmost point (smallest x), if they are multiple choose the lowest (smallest y). No three consecutive vertices should lie on the same line. 
```
N
sx_1 sy_1
sx_2 sy_2
...
sx_N sy_N
```

#### TEST 2: Testing correctness of my Minkowski sum of multiple convex polygons
Input format: The first line contains $n$, the number convex polygons. The $n$ convex polygons follow. The description of the ith polygon begins with $m_i$, the number of vertices. The next $m_i$ lines contains the coordinates of the vertices. 
Input example:
```
3
3
0 0
1 0
0 1
4
1 1
1 2
0 2
0 1
3
2 2
1 2
2 1
3
1 2
2 3
1 3
```
$2 \le n \le 100$
$3 \le m_i \le 10^3$
$-10^3 \le x_{ij}, y_{ij} \le 10^3$
For each polygon, no three consecutive vertices will lie on the same line. All numbers are integers.

Output format: The number of vertices of the Minkowski sum N on the first line, then N lines where the ith line is coordinates of the ith point. Points should be outputted in CCW order with the min point outputted first. The min point is the leftmost point (smallest x), if they are multiple choose the lowest (smallest y). No three consecutive vertices should lie on the same line. 
```
N
sx_1 sy_1
sx_2 sy_2
...
sx_N sy_N
```

### Problems:
These are the problems I solved using my implementation (or observations) of Minkowski sums. My solutions along with an explanation are in the problems folder.

- Robert Hood: https://open.kattis.com/problems/roberthood
- Engines: https://atcoder.jp/contests/abc139/tasks/abc139_f
- Mogohu-Rea Idol: https://codeforces.com/contest/87/problem/E
- Multiple Choice Test: http://usaco.org/index.php?page=viewproblem2&cpid=1190
- Geometers Anonymous Club: https://codeforces.com/problemset/problem/1195/F
- Monocarp and a Strategic Game: https://codeforces.com/contest/1841/problem/F

### File Overview:
/problems: problem solutions and explanations
/src: Minkowski sum implementations
/tests/bookcode: Book code used in tests 
/notes: notes about Minkowski sum

### Resources:

http://usaco.org/current/data/sol_prob3_platinum_jan22.html (Editorial for Multiple Choice Test)
Explanation of offsets and source for Minkowski sums of multiple convex polygons.

https://cp-algorithms.com/geometry/minkowski.html
Source for Minkowski sum of two convex polygons. Their description of the algorithm was not very intuitive to me. 

https://faculty.sites.iastate.edu/jia/files/inline-files/15.%20Minkowski%20sum.pdf
Pseudo code for Minkowski sums of two convex polygons, and good explanation to understand the intuition behind it. 

https://codeforces.com/blog/entry/68471 (Editorial for problem Geometers Anonymous Club).
Another explanation of Minkowski Sums. 

https://prase.cz/kalva/short/soln/sh973.html
Thinking about offsets in this way was helpful to me. 

