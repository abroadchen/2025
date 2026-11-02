//
// Created by Psy.C on 2026/11/2.
//

/**
真正学会的起点..
用两个多重集合 l、r 分别存所有线段的左端点最小值和右端点。
multiset（可重复、有序）方便快速取最大/最小
对每条线段 i，先从集合中拿掉它的左右端点（模拟"删除该线段"）。
此时剩余条线段的"最小右端点"即 *r.begin()，"最大左端点"即 *--l.end()（multiset 末位前一个）。
二者之差 = 剩余线段公共交叠的最大长度，更新 res。
之后把删除的端点恢复，继续下一轮
输出所有"去掉一条线段"方案中最大的跨距值
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

// constexpr int N = 3e5+5;
//
// struct node { int l, r; } q[N];
//
// int n, res;
// multiset<int> l, r;
// int main() {
//     fast;
//     cin >> n;
//     rep(i,n) {
//         cin >> q[i].l >> q[i].r;
//         l.insert(q[i].l); r.insert(q[i].r);
//     }
//     rep(i,n) {
//         l.erase(l.find(q[i].l));
//         r.erase(r.find(q[i].r));
//         res = max(res, *r.begin()-*--l.end());
//         l.insert(q[i].l); r.insert(q[i].r);
//     }
//     cout << res << '\n';
//     return 0;
// }

constexpr int N = 1e6+5;

struct node {
    int l, r, id;
    bool operator<(const node &o) const {
        return l < o.l;
    }
} a[N];
priority_queue<int, vector<int>, greater<>> q;

int main() {
    fast;
    int n; cin >> n;
    rep(i,n) { cin >> a[i].l >> a[i].r; a[i].id = i; }
    sort(a+1, a+n+1);
    int ans = 0;
    rep(i,n) {
        q.push(a[i].r);
        if (q.size() > n-1) q.pop();//只保留最大的 n-1 个右端点(弹出最小)
        if (q.size() == n-1 && ans < q.top()-a[i].l)
            ans = q.top()-a[i].l;
    }
    cout << ans;
    return 0;
}

/**
线段按左端点 l 从小到大排序
核心思想：删除某条线段后，剩余 n-1 条中"最小的右端点" = 原集合里除被删那条外的最小右端点。
由于按左端点升序处理，堆里始终保持"当前这 n-1 条中的最小右端点"（即 q.top() 是当前被当作"剩下所有线段的 min r"）。
q.top() - a[i].l：最小右端点减去当前(同时也是被删候选)线段的左端点，即删除第 i 条后重叠跨度。取最大即为答案。
为什么成立：左端点最大的那条作为被删候选时，其余 n-1 条的最小右端点被堆正确维护，跨距最大，故取 n-1 个右端点里最小的即可



 */