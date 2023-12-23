#include "../bookcode/template.h"
#include "../bookcode/ConvexHull.h"

const int MX = 1e9;

long long rand(long long a, long long b) {
    return a + rand() % (b - a + 1);
}

vector<Point<ll>> generate_points(int n) {
    assert(n >= 0);
    vector<Point<ll>> ans;
    while(n--) {
        ll x = rand(-MX, MX);
        ll y = rand(-MX, MX);
        ans.push_back(Point<ll>(x, y));
    }
    return ans;
} 

int main(int argc, char* argv[]) {
    // seed the generator
    srand(atoi(argv[1]));

    int n = rand(1, 10000);
    int m = rand(1, 10000);
    vector<Point<ll>> A = convexHull(generate_points(n));
    vector<Point<ll>> B = convexHull(generate_points(m));

    cout << A.size() << endl;
    for (auto &pt: A) {
        cout << pt.x << " " << pt.y << endl;
    }
    cout << B.size() << endl;
    for (auto &pt: B) {
        cout << pt.x << " " << pt.y << endl;
    }


    return 0;
}