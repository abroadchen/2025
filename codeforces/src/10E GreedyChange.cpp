//
// Created by Psy.C on 2025/9/14.
//


#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int inf = 2e9;
int main() {

    int n, ans = inf; scanf("%d", &n);
    vector<int> c(n);
    for (int& x : c) scanf("%d", &x);

    auto val = [&](int x) {
        int res = 0;
        for (int v : c) res += x / v, x %= v;
        return res;
    };

    for (int i = 1; i < n; ++i) {
        int s = c[i - 1] - 1, x = s, m = 0;
        for (int j = i; j < n; ++j) {
            m += x / c[j]; x %= c[j];
            if (m + 1 < val(s - x + c[j]))
                ans = min(ans, s - x + c[j]);
        }
    }

    printf("%d\n", ans == inf ? -1 : ans);


    return 0;
}