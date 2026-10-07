//
// Created by Psy.C on 2026/10/7.
//
/**
双指针（尺取）‍：对每个左端点 i，r[i] = 使得 a[j] - a[i] <= x 的最远右端点 j。即 r[i] 是以 a[i] 为起点、长度上限 x 的区间能覆盖到的最远下标。
由于 a 已排序，双指针单调，O(n)
用差分数组 d 做区间覆盖加法（类似"跳区间覆盖"问题）。
if (r[1] >= k) d[k]++, d[r[1]+1]--;：若以 a[1] 为左端能覆盖到第 k 个及以后，则给区间 [k, r[1]] 加覆盖。
之后对每个 i，若位置 i 已被覆盖（s>0，说明能以某个早先左端拓展到这里），则以 i+1（即 a[i+1]）为新左端，覆盖 [i+k, r[i+1]]，通过差分给这个区间加 1。
最终若某处覆盖数 s>0，说明存在一条能连续走到最后（覆盖到 n）的路径，check 返回 true。
语义：能否用长度上限为 x 的覆盖段，从 a[1] 起每次向前跳 k 个点（每个段内至少 k 个点），一路覆盖下去。这是典型的"最小化最大段长 / 段内点数至少 k 的段覆盖可行性"二分判定
标准极小化二分：找使 check(x) 为真的最小 x。check 单调（x 越大越容易覆盖）
排序后二分答案，输出最小可行的 x
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3e5+10, inf = 1e9;

int r[N], n, a[N], d[N], k;
bool check(int x) {
    memset(r, 0, sizeof r);
    for (int i = 1, j = 1; i <= n && j <= n; ++i) {
        if (j < i) j = i;
        while (j+1 <= n && a[j+1] - a[i] <= x) j++;
        r[i] = j;
    }
    memset(d, 0, sizeof d);
    int s = 0;
    if (r[1] >= k) { d[k]++; d[r[1]+1]--; }
    for (int i = 1; i <= n; ++i) {
        s += d[i];
        if (s > 0) {
            int L = i+k, R = r[i+1];
            if (L > R) continue;
            d[L]++; d[R+1]--;
        }
    }
    return s > 0;
}

int find(int l, int r) {
    while (l < r) {
        int mid = (l+r)>>1;
        if (check(mid)) r = mid;
        else l = mid+1;
    }
    return l;
}

int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a+1, a+1+n);
    cout << find(0, inf) << '\n';
    return 0;
}