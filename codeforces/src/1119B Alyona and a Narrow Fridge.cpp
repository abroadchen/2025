//
// Created by Psy.C on 2026/11/24.
//

/**
真正学会的起点..
s=数值 id=原下标  按数值升序 按原下标恢复
把每个原始开销 a[i].s 压缩成离散排名（1..len），原值存进 t[排名]
前 x 个（
a 已按要求——注意此时 a 已被离散化，需按原开销选最便宜的 x 个，这里用桶排展开成升序排名 b[]，再取对应原值 t[]——二分体是"从最便宜的 x 个任务里选出"）。
隔一个取一个（i-=2）累加开销：每次取最贵的那个、同时配一个最便宜的（i 从 x 往 2 递减，i-1 是它前面的更便宜搭档），累加到 sum；sum>h 则不可行返回 0。
全部不超即可行
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;

constexpr int N = 1e4+5;

struct node { int s, id; } a[N];
bool cmp(node u, node v) {
    if (u.s != v.s) return u.s < v.s;
    return u.id < v.id;
}
bool cmp2(node u, node v) { return u.id < v.id; }

int bl, bx[N], n, b[N], t[N], h;
bool check(int x) {
    bl = 0;
    rep(i,x) ++bx[a[i].s];//统计前 x 个里每种排名的数量
    rep(i,n) { while (bx[i] > 0) { --bx[i]; b[++bl] = i; } }//桶排序展开回排名序列（升序）
    int sum = 0;
    for (int i = x; i >= 1; i -= 2) {
        sum += t[b[i]];
        if (sum > h) return 0;
    }
    return 1;
}

int len;
int main() {
    fast;
    cin >> n >> h;
    rep(i,n) { cin >> a[i].s; a[i].id = i; }
    sort(a+1, a+1+n, cmp);
    t[1] = a[1].s; a[1].s = len = 1;
    for (int i = 2; i <= n; i++) {
        if (a[i].s != a[i-1].s) t[++len] = a[i].s;//不同值→新排名
        a[i].s = len;//把数值换成排名
    }
    sort(a+1, a+1+n, cmp2);//恢复原顺序（按 id）
    int l = 1, r = n, mid;
    while (l <= r) {
        mid = (l+r+1)>>1;
        if (l == r) break;
        if (check(mid)) l = mid; else r = mid-1;
    }
    cout << l;
    return 0;
}