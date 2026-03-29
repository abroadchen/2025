//
// Created by Psy.C on 2026/3/29.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a, b, c;
int main() {
    fast;
    cin >> a >> b >> c;
    double p = sqrt(b*b-4*a*c), x1 = (-1.*b+p)/(2*a), x2 = (-1.*b-p)/(2*a);
    if (x1 < x2) printf("%.7lf\n%.7lf\n", x2, x1);
    else printf("%.7lf\n%.7lf\n", x1, x2);
    return 0;
}