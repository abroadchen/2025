//
// Created by Psy.C on 2025/9/18.
//
/*
*maxn: 最大区间数
n: 实际区间数
vis[maxn]: 标记数组，记录哪些区间已被覆盖
v: 存储选择的点
 *
 *按右端点升序排序，右端点相同时按左端点升序排序
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

static const int maxn=1e3+10;
int n;
bool vis[maxn];
vector<int> v;

struct Seg {
    int l, r;
    void input() {
        scanf("%d%d", &l, &r);
        if (l > r) swap(l, r);
    }
    bool operator<(const Seg& b) const {
        if (r == b.r) return l < b.l;
        return r < b.r;
    }
} seg[maxn];

int main() {
    scanf("%d",&n);
    for (int i = 0; i < n; ++i) seg[i].input();
    sort(seg, seg+n);

    for (int i = 0; i < n; ++i) {
        if (vis[i]) continue;
        v.push_back(seg[i].r);
        vis[i] = true;

        for (int j = i + 1; j < n; ++j) {
            if (vis[j]) continue;
            if (seg[j].l <= seg[i].r && seg[i].r <= seg[j].r) vis[j] = true;
        }
    }
    printf("%d\n", v.size());
    for (int i = 0; i < v.size(); ++i) printf("%d ", v[i]);
    return 0;
}