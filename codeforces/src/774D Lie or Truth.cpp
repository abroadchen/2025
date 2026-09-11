//
// Created by Psy.C on 2026/9/11.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int cmp(const void* a, const void* b) {
    long la = *((long *) a), lb = *((long*)b);
    return (la > lb) - (la < lb);
}

int main() {
    fast;
    long n, l, r; cin >> n >> l >> r; --l, --r;
    long *a = (long*)malloc(n * sizeof(long)), *b = (long*)malloc(n * sizeof(long));
    for (long p = 0; p < n; ++p) cin >> a[p];
    for (long p = 0; p < n; ++p) cin >> b[p];
    int f = 1;
    for (long p = 0; p < l; ++p)
        if (a[p] != b[p]) { f = 0; break; }
    for (long p = r+1; p < n; ++p)
        if (a[p] != b[p]) { f = 0; break; }
    qsort(a, n, sizeof(long), cmp);
    qsort(b, n, sizeof(long), cmp);
    for (long p = 0; p < n; ++p)
        if (a[p] != b[p]) { f = 0; break; }
    puts(f ? "TRUTH" : "LIE");
    return 0;
}