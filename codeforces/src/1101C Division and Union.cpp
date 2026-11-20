//
// Created by Psy.C on 2026/11/20.
//

/**
真正学会的起点..node 存一个区间 [l, r]，e[] 存所有区间。
cmp 排序规则：按左端点 l 升序排序。
T 组测试；n 区间个数；p 记录"分界位置"；L[], R[] 保存每个区间原始顺序的左右端点（用于最后按原顺序输出）；len 变量用于扫描
每组数据先把 p 复位为 -1；
读入 n 个区间，同时备份到 L[i]、R[i]（保持原顺序，因为后面要对 e 排序会打乱顺序）
按左端点升序排序所有区间；len 初始化为最小区间的左端点
扫描找分界点：遍历排序后的区间，维护当前"连续覆盖的最右端" len：

若当前区间与已覆盖区间相交（e[i].l <= len）且右端更远（e[i].r > len），就把 len 扩展到 e[i].r，即这些区间会归为同一组（因为它们两两相连成一片连续区间）；
否则（e[i].l > len，出现了第一个"断开"的区间）：如果它的右端 e[i].r > len，说明这里有一道明显裂缝，记录 p = len（分界点）并 break。
实际上这个逻辑在找：第一组连续覆盖区的右边界，p 就是这一组的最大右端点。

更准确地说：若所有区间首尾相连成一片（任何两个相交都合在一起），就分不成两组，此时 p 不会被设置，仍为 -1
若没有找到分界点 p，说明所有区间交叠成一片、无法分成两个不相交的组，输出 -1 并进入下一轮
按原始顺序（用备份的 R[i]）：若区间的右端点 R[i] <= p，说明它在第一组（裂缝左侧），输出 1；否则输出 2
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 1e5+10;

struct node { int l, r; } e[N];
int cmp(node a, node b) { return a.l < b.l; }

int T, p, n, L[N], R[N], len;
int main() {
    fast;
    cin >> T;
    while (T--) {
        p = -1; cin >> n;
        rep(i,n) { cin >> e[i].l >> e[i].r; L[i] = e[i].l, R[i] = e[i].r; }
        sort(e+1,e+n+1,cmp); len = e[1].l;
        rep(i,n) {
            if (e[i].r > len && e[i].l <= len) len = e[i].r;
            else { if (e[i].r > len) { p = len; break; } }
        }
        if (p == -1) { cout << -1 << '\n'; continue; }
        rep(i,n) {
            if (R[i] <= p) cout << 1 << ' ';
            else cout << 2 << ' ';
        }
        cout << '\n';
    }
    return 0;
}