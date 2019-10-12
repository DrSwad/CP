#include<bits/stdc++.h>

using namespace std;

long long GCD(long long a, long long b) { return (b == 0) ? a : GCD(b, a % b); }

struct GCD_type { long long x, y, d; };

GCD_type ex_GCD(long long a, long long b) {
    if (b == 0) return {1, 0, a};
    GCD_type pom = ex_GCD(b, a % b);
    return {pom.y, pom.x - a / b * pom.y, pom.d};
}

int main() {


    return 0;
}
