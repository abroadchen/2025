//
// Created by Psy.C on 2026/9/6.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ud unsigned
#define ll long long
using namespace std;

struct quad {
    ud s1, s2, c1, c2;
    quad(int s1, int s2, int c1, int c2) : s1(s1), s2(s2), c1(c1), c2(c2) {}
};
ud get_hash(ud s1, ud s2, ud c1, ud c2) {
    return (s1<<21)|(s2<<10)|(c1<<5)|c2;
}
quad trans(ud x) {
    return quad(x>>21, (x&((1<<21)-1))>>10, (x&((1<<10)-1))>>5, x&((1<<5)-1));
}


int main() {
    fast;

    return 0;
}