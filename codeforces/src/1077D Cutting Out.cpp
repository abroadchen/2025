//
// Created by Psy.C on 2026/11/14.
//

/**
真正学会的起点..
用 cnt[] 统计每个值出现次数。
遍历 n 个数，遇到一个还没被清零的 a[i]，就把它和它的次数加入 v，并把 cnt[a[i]] 清零，达到去重效果（每个值只入 v 一次）
自定义 operator<：按出现次数 c 从大到小排序。
这样 v[0] 是出现次数最多的值。
二分范围 [1, v[0].c]（最大出现次数）。
对每个 mid，计算"如果每个值被拆分重复 mid 次"，能产生多少个元素：sum += v[i].c / mid。
如果 sum >= k，说明 mid 还不够大（还能更大），l = mid+1；否则 r = mid-1。
二分结束后，l-1 或 r 是满足 sum>=k 的最大 mid 值（最后 l 会比合法值大 1）
实际用 l-1（二分得到的最大可行 mid）作为每个值的重复基数。
对每个值，输出 v[i].c / (l-1) 次，直到凑满 k 个
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 2e5+5;

struct node {
    int val, c;
    bool operator<(const node& o) const { return c > o.c; }
};
vector<node> v;
int a[N], cnt[N];
void solve() {
    int n, k; cin >> n >> k;
    rep(i,n) cin >> a[i], cnt[a[i]]++;
    rep(i,n) if (cnt[a[i]]) {
        v.push_back({a[i], cnt[a[i]]});
        cnt[a[i]] = 0;
    }
    sort(v.begin(), v.end());
    int l = 1, r = v[0].c, sum, len = v.size();
    while (l <= r) {
        int mid = (l+r)>>1; sum = 0;
        for (int i = 0; i < len; i++) {
            if (sum >= k) break;
            int d = v[i].c/mid;
            sum += d;
        }
        if (sum >= k) l = mid+1; else r = mid-1;
    }
    sum = 0, r = 0;
    for (int i = 0; i < len; i++) {
        if (sum >= k) break;
        int d = v[i].c/(l-1); sum += d;
        while (d--) {
            cout << v[i].val << ' ';
            r++;
            if (r >= k) break;
        }
    }
}


int main() {
    fast;
    solve();
    return 0;
}