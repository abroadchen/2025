//
// Created by Psy.C on 2026/11/12.
//

/**
真正学会的起点..
n：位置数量；r：覆盖半径；v[]：该位置是否有装置；ans：答案
p 表示当前最左边还没有被覆盖的位置
x, y：从 p 能覆盖到的合法放装置区间。

y = p+r-1：在 p 左侧放置装置时它能覆盖到的最右位置（若放装置于 p-r+1 处，能覆盖 [p-r+1, p]，故 p 由 [p-r+1, p] 内的装置覆盖到，最小放装置的右界是 y）。
其实更准确看：能从 x= p-r+1 到 y=p+r-1 这个范围内放置装置都能覆盖到 p
从 y 往 x 从右往左找第一个 v[i] 非零（可以放置装置）的位置 idx。
从右往左搜保证贪心最贪：选最靠右的可放位置，这样一个装置能覆盖最多的右侧点位

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1010;

int n, r, v[N], ans;
int main() {
    fast;
    cin >> n >> r;
    for (int i = 1; i <= n; i++) cin >> v[i];
    int p = 1;//贪心指针：从 p 位置开始，希望被覆盖的最左未覆盖点
    while (p <= n) {//只要还有未覆盖位置
        int idx = 0, y = min(p+r-1,n), x = max(p-r+1,1);
        for (int i = y; i >= x; i--) if (v[i]) { idx = i; break; }
        if (!idx) { cout << -1 << '\n'; return 0; }//找不到可放装置的合适点 → 无解
        p = idx + r;//这个装置能覆盖到 idx+r 处，所以最左未覆盖点跳到 idx+r+...
        ans++;//装置数量 +1
    }
    cout << ans << '\n';
    return 0;
}