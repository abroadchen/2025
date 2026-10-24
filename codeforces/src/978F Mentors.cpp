//
// Created by Psy.C on 2026/10/22.
//
/**
node 记录元素值 v、原位置 p、答案 ans。
cmp 按值升序排序；cmp2 按原位置恢复排序。
find(x)：在已按值排序的 a 里二分，找第一个 ≥ x 的下标。等价于 lower_bound，返回"值 < x 的元素个数 + 1"（即第一个 ≥x 的位置下标
多重测试直到输入结束（EOF）。
读入每个元素的值 v、记录原位置 p。
读入 k 组 (x,y) 边：
只保留"较大值 → 较小值"的单向邻近关系：若 a[x].v > a[y].v，则把 y 记入 q[x]；反之若 a[x].v < a[y].v，把 x 记入 q[y]。
若两者值相等，则这条边被忽略（不记录）
按值排序后，对每个元素 i（此时按下标 1..n 是值有序的）：
find(a[i].v) - 1 = 值严格小于 a[i].v 的元素个数。
减去 q[a[i].p].size() = 与该位置相连且值更小的邻居个数（因为这些"小于自己的相邻点"本应计入，但题意要求排除）。
得到 ans。
再按原位置 p 恢复顺序并输出每个位置答案
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 2e5+5;

struct node { int v, p, ans; } a[N];
bool cmp(const node &x, const node &y) { return x.v < y.v; }
bool cmp2(node x, node y) { return x.p < y.p; }

int n;
int find(int x) {
    int l = 1, r = n;
    while (r >= l) {
        int mid = (l+r)>>1;
        if (a[mid].v >= x) r = mid-1;
        else l = mid+1;
    }
    return l;
}

int k, i, x, y;
vector<int> q[N];
int main() {
    fast;
    while (cin >> n >> k) {
        for (i = 1; i <= n; i++) { cin >> a[i].v; a[i].p = i; a[i].ans = 0; q[i].clear(); }
        for (i = 0; i < k; i++) {
            cin >> x >> y;
            if (a[x].v > a[y].v) q[x].push_back(y);
            else if (a[x].v < a[y].v) q[y].push_back(x);
        }
        sort(a+1, a+n+1, cmp);
        for (i = 1; i <= n; i++) a[i].ans = find(a[i].v)-1-q[a[i].p].size();
        sort(a+1, a+n+1, cmp2);
        for (i = 1; i <= n; i++) cout << a[i].ans << ' ';
        cout << '\n';
    }
    return 0;
}