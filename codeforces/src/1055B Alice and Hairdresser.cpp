//
// Created by Psy.C on 2026/11/9.
//

/**
真正学会的起点..
n：数组大小
m：操作数
l：阈值
cnt：当前"高亮连续段"个数
遍历每个位置，若 a[i] > l（高亮）：
如果它是第 0 个位置，那我看到一个新的高亮起点，cnt++。
否则，只有当左边邻居不高亮（a[i-1] <= l）时，说明这个高亮点属于一段新的连续高亮块，cnt++。
若左边邻居也高亮，则该位置是同一段的延续，不新增段数。
这样一遍扫完，cnt 就是初始的段数
c==0 直接输出 cnt，很简单。重点在 c==1 的单点加值后维护段数
if (a[p] > l) continue;：加值前该位置本来就高亮，那么这次 +=d 不会改变高亮状态，段数必然不变，直接跳过。
a[p] += d; 后再检查 if (a[p] <= l) continue;：加完之后仍然不高亮，同样段数不变，跳过
当位置 p 从"不高亮"变为"高亮"（点亮），它对"段数"的影响只看左右两个邻居：

左右邻居都不高亮（a[p-1]<=l && a[p+1]<=l）——点亮 p 后，p 自己组成一个独立新段 → cnt++。
左右邻居都高亮（a[p-1]>l && a[p+1]>l）——点亮 p 后，p 把原先左右两段连成了一段 → 段数减少 1，cnt--。
只有一边高亮（左高右不高，或左不高右高）——点亮 p 后，p 只是延伸了那一段，段数不变，什么也不做。
而端点特判（p==0 或 p==n-1）只是因为端点只有一侧邻居，逻辑退化为"只看唯一一个邻居是否高亮"，若邻居不高亮则新起一段 cnt++，若邻居高亮则延伸、段数不变
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e5+5;

ll n, m, l, cnt, a[N];
int main() {
    fast;
    cin >> n >> m >> l;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] > l) {
            if (i == 0) cnt++;
            else { if (a[i-1] <= l) cnt++; }
        }
    }
    while (m--) {
        int c; cin >> c;
        if (c == 0) cout << cnt << '\n';
        else {
            int p, d; cin >> p >> d; p -= 1;
            if (a[p] > l) continue;
            a[p] += d;
            if (a[p] <= l) continue;
            if (p != 0) {
                if (p == n-1) { if (a[p-1] <= l) cnt++; }
                else {
                    if (a[p-1] > l && a[p+1] > l) cnt--;
                    else if (a[p-1] <= l && a[p+1] <= l) cnt++;
                }
            } else { if (a[p+1] <= l) cnt++; }
        }
    }
    return 0;
}