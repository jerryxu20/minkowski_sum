# Solutions

### [Robert Hood](https://open.kattis.com/problems/roberthood)

Given a set of points, find the maximum distance between any pair of points. The distance between two points $p$ and $q$ is $||p - q||$.

A - the original set of points
B - the original set of points, but their x and y values are negated

The Minkowski sum of A and B is the set of all differences between any two points from the original set.

Since we are looking for the maximum distance, we only need to consider the convex hull of the Minkowski sum of A and B, which we can find by taking the Minkowski sum of the convex hull of A and the convex hull of B.

An alternative solution is taking the convex hull of the original set of points and then using binary search or rotating calipers to find the max distance between two points on the hull. 

### [Engines](https://atcoder.jp/contests/abc139/tasks/abc139_f)

Each engine is a vector (x, y). The problem asks us to find the maximum distance from the origin that the sum of a subset of engines can take us. Considering all subset of engines (2^100) is too slow, but it is only necessary to consider the convex hull of all subsets of engines.

Think of each engine as a line segment [(0, 0), (x, y)], which represents the choice to either take the engine or not. Then the problem reduces to finding the point with the largest magnitude on the Minkowski sum of all the line segments. Since the number of engines is small and each engine only has two points, either Minkowski sum algorithm works. 


Thinking in terms of Minkowski sums is not needed as long you still make the convexity observation. We can keep track of the current hull, starting with a set that only contains (0, 0) and then for each new engine, compute a new set of points which consists of the old hull as well as each point in the old hull added with the engine's point. Then take the convex hull of the new set to update the current hull. This is fast enough because we know from Minkowski sums that the size of the hull can only grow linearly with the number of engines. Even without the last observation, you could convince yourself that it would be hard to design a testcase that makes the convex hull grow massively and just submit that solution. 

### [Mogohu-Rea Idol](https://codeforces.com/contest/87/problem/E)

In this problem there are three convex polygons (A, B, C) and multiple queries. Each queries asks if it is possible for a certain point (x, y) to be the center of a triangle formed by choosing a point from each polygon as a vertex. 

C - center of the triangle
v - vertex of the triangle
$$C = \frac{v_1 + v_2 + v_3}{3} \implies 3C = v_1 + v_2 + v_3$$

We need to check if $3C$ belongs to the set of points formed by summing a point from A, a point from B, and a point from C. This set of points is just the Minkowski sum of A, B, and C. 

We can find the convex hull of this sum using either Minkowski sum algorithm. Then for each $C$ in the query, check if $3C$ is inside or on the hull. To do this split the hull into top hull/bottom hull and binary search to find the top and bottom edge that this point is line with and check if it's bound by those edges (or use book code).


### [Multiple Choice Test](http://usaco.org/index.php?page=viewproblem2&cpid=1190)
In this problem we are given n sets of points. We need to select one point from each set and sum them up to get as far away from the origin as possible. The set of all possible points we can obtain is the Minkowski sum of all n sets. We cannot compute the Minkowski sum of arbitrary sets fast, but since the problem only asks for the largest magnitude achievable, we only need the convex hull of the Minkowski sum. 

The convex hull of the Minkowski sum of two sets A and B is the same as the Minkowski sum of the convex hull of A and the convex hull of B. This idea can be extended to multiple sets. 

Reduce each set of points to its convex hull. This results in n convex polygons. Compute the Minkowski sum of all n polygons then find the point with largest magnitude. 

If we compute the Minkowski sum of all n polygons at once, it is fast enough. 

### [Geometers Anonymous Club](https://codeforces.com/contest/1195/problem/F)
Given n convex polygons, we must answer queries about them. Each query, $[l_i, r_i]$ asks for the number of vertices in Minkowski sum of polygons$[l_i .. r_i]$. This problem requires an observation about Minkowski sums. 

Consider the algorithm to compute the Minkowski sum of k polygons. The offsets of all k polygons are put into a single list and sorted by angle. Starting from an initial point, the algorithm walks CCW around the convex hull of the Minkowski sum using the offsets.

The initial point is the sum of the minimum points from each polygon. Then as we go through the offsets, we continuously update the current point by adding each offset. At any iteration, we know the current point will be a vertex on the final sum if there is no next offset, or the next offset has a different angle than the current offset.

Offsets with the same angle will always be next to each other when sorted, meaning they will only contribute one vertex. Therefore the number of vertices is equal to the number of unique angles in the offsets. 

This reduces the problem to answering distinct value range queries. To avoid computing angles, we can put all offsets in a list and sort them. Then map each run of consecutive offsets with the same angle to an integer value. Offsets from different runs should have different values. After this each polygon just becomes a set of integers.  

We will answer the queries offline using a segment tree. Sort queries by right end point (smallest first). 


```
r: the right end point of the current query
prev: the right end point of the previous query

last_seen[v]: the set that value v was last seen in. 

seg[i]: the number of values from set[i] that are not in set[i + 1...r]. Can also think of this as the number of values from set[i] that are most recently seen in set[i]. 

For each query (l, r):
    For each set between prev + 1 and r (sets we haven't seen so far):
        For each value v in the set: 
            - if this value was last seen at some previous set decrement seg[last_seen[v]]
            - increment seg[current set]
            - set last_seen[v] = current set 

    The answer is the number of values from set[l] that are not in set[l + 1 .. r] + the number from values from set[l + 1] that are not in set[l + 2...r] + ... + the number of values from set[r]. 
    This is just the sum of (l,r) on the segment tree. 
```


### [Monocarp and a Strategic Game](https://codeforces.com/contest/1841/problem/F)
This is the problem where I first came across Minkowski sums. 

First, we need to make an observation about happiness values. Notice that the happiness of humans and orcs depends only on the number of humans and orcs. The happiness of elves and dwarves depends only on the number of elves and dwarves. There are two groups - humans/orcs and elves/dwarves. Consider the happiness value of each group.

a - number of humans
b - number of orcs
c - number of elves
d - number of dwarves
h - happiness
$h_{ab} = a(a-1) + b(b - 1) - 2ab + a + b$
$h_{ab} = a^2 - a + b^2 - b - 2ab + a + b$
$h_{ab} = a^2 + b^2 - 2ab = (a-b)^2$

The same can be done for elves/dwarves. The total happiness is 

$h_{total} = (a-b)^2+(c-d)^2 = ||(a-b, c-d)||^2$

For each group $a_i, b_i, c_i, d_i$, represent it as a point $(a_i-b_i, c_i-d_i)$. Accepting a group is the same as adding it to the point that represents the current state of your city. This reduces to finding the max magnitude of the sum of a subset of points, which is the same as engines. 

Again represent the choice of accepting/rejecting each group as a line segment $[(a_i-b_i, c_i-d_i), (0,0)]$. Then compute the Minkowski sum of all line segments and find the point with the largest magnitude.

For this problem the bounds are large, so we need to compute the Minkowski sum of all polygons at once and use 128 bit integers. 

