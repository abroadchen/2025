//
// Created by Psy.C on 2026/9/18.
//
/**
b[val]：记录值为 val（下标减1）的元素在序列中出现的所有位置。
ord[]：出现位置数组。
h：当前处理到的"该元素下一个出现位置"的指针。
n：该元素出现总次数。
vis[val]：该元素当前是否占用缓存槽。
a[i]：原始序列。
ord 初始化为 inf（无穷大）表示"之后不再出现"。
对每个元素 a[i]-1，把它出现的位置 i 存进 ord[]，出现次数 n++。
没出现的位置保持 inf。
注意：结构体里 n 表示该元素出现次数，ord[0..n-1] 是按顺序（升序）出现的位置
顺序遍历序列。
若当前元素不在缓存（vis==0）→ 一次未命中 mn++，并把它调入（vis=1）。
若缓存已满（tot==k，已占用 k 个槽），需淘汰其中一个元素。淘汰策略是 Belady 最优算法：淘汰"下一次出现位置最远/最晚"的那个缓存元素（即 b[t].ord[b[t].h] 最大，h 是该元素已经扫到的下一个出现位置指针）。这在离线场景下是最优的。
否则缓存未满，直接占用新槽 tot++。
关键点：无论当前元素是否在缓存，处理完后都要 b[a[i]-1].h++ 推进该元素的"下一个出现位置"指针。这样扫描到后面时，b[t].ord[b[t].h] 表示元素 t 未来最近一次出现的位置，用于 Belady 淘汰决策。
d：记录被选中淘汰的元素编号
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 85, inf = 0x3f3f3f3f;
struct node { int ord[N], h, n; } b[N];
int a[N];
bool vis[N];
int main() {
    fast;
    int n, k; cin >> n >> k;
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= n; ++j) b[i].ord[j] = inf;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        b[a[i]-1].ord[b[a[i]-1].n] = i;
        b[a[i]-1].n++;
    }
    int d = 0, mn = 0, tot = 0;
    for (int i = 0; i < n; ++i) {
        if (vis[a[i]-1] == 0) {
            mn++; vis[a[i]-1] = 1;
            if (tot == k) {
                int mx = -1;
                for (int t = 0; t < n; ++t) {
                    if (vis[t] && b[t].ord[b[t].h] > mx) {
                        mx = b[t].ord[b[t].h];
                        d = t;
                    }
                }
                vis[d] = 0;
            } else tot++;
        }
        b[a[i]-1].h++;
    }
    cout << mn << '\n';
    return 0;
}