//
// Created by Psy.C on 2026/10/22.
//
/**

先按 l 降序，再按 r 升序

若当前区间与下一个区间 l 相同（因升序排列，l 相同的相邻）：此时 tr[i].r <= tr[i+1].r?? 不对——排序是 l 相同 r 升序，所以 tr[i].r <= tr[i+1].r。则 tr[i]（r 小者）‍包含于 tr[i+1]（r 大者），即 tr[i+1] ⊇ tr[i]。
但排序 l 降序，是否 l 相同一定相邻？取决于排序稳定性，这里用 cmp 相等时按 r 升序，l 相同会聚在一起。找到即输出两个 id，结束
t 保存的是此前扫描过的、r 最大的区间。
由于按 l 降序，之前区间的 l ≥ 当前区间的 l。
若当前 tr[i].r >= t.r：当前区间的 r 不低于之前最大 r 区间，同时当前 l 更小/相等 → 所以 t 的区间被 tr[i] 包含（tr[i] 的 l 更小或等、r 更大或等，即 tr[i] ⊇ t）。
则输出 t.id（被包含者）和 tr[i].id（包含者），结束。
每轮末尾 t = tr[i]：更新"r 最大"的基准为当前区间（因为扫描方向 l 递减，用当前更大的 r 更新 t）
扫描完 n 个仍无包含关系，输出 -1 -1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 3e5+5;

struct node { int l, r, id; } tr[N];
bool cmp(node a, node b) {
    if (a.l > b.l) return true;
    if (a.l == b.l) return a.r < b.r;
    return false;
}

int main() {
    fast;
    int n; cin >> n;
    for (int i = 0; i < n; i++) cin >> tr[i].l >> tr[i].r, tr[i].id = i+1;
    sort(tr, tr+n, cmp);
    node t{};
    for (int i = 0; i < n; i++) {
        if (i < n-1 && tr[i].l == tr[i+1].l) {
            cout << tr[i].id << ' ' << tr[i+1].id;
            return 0;
        }
        if (i && tr[i].r >= t.r) {
            cout << t.id << ' ' << tr[i].id;
            return 0;
        }
        t = tr[i];
    }
    cout << "-1 -1";
    return 0;
}