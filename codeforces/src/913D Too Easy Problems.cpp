//
// Created by Psy.C on 2026/10/12.
//
/**
每个任务有属性 a（某种门槛/重要度）和 t（耗时）。
参数 q 是总时间预算。
通过二分 k，判断：是否存在一组"恰好/至少 k 个、且每个的 a ≥ k"的任务，其总耗时 ≤ q。
满足则增大 k（l = mid），否则减小（r = mid），最后输出最大的可行 k 及选出的任务。
其实更准确地说，这题的检验逻辑是：能否选出 k 个任务，每个满足 a ≥ k，且耗时和不超 q
vc：所有任务（输入全部）。
vt：check 时临时筛选出的"a ≥ k"的任务。

先把所有 a ≥ k 的任务拷进 vt（候选集）。
按耗时 t 升序排序——贪心：优先做耗时短的任务，这样才能在有限时间 q 内做尽可能多。
依次尝试做：若剩余时间 x 不足当前任务耗时 t 则 break；否则计数 +1、x -= t。
返回 cnt >= k：能否在预算内做满至少 k 个。
于是 check(k, q) 为真 ⇔ 存在 k 个"a ≥ k"的任务，且总耗时 ≤ q
二分 k ∈ [0, inf]（inf=3e5），找最大的可行 k。
check(mid, q) 可行 → 把 l 提升到 mid，并保存当时的 vt（贪心选中的那 k 个任务）到 ans。
否则 r = mid。
最终 l 是最大可行 k；ans 里前 l 个是选中的任务。
输出 l（两次），然后输出选中任务的 id
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 2e5+5, inf = 3e5;

struct node { int a, t, id; };

vector<node> vt, vc;
bool check(int k, int x) {
    vt.clear();
    for (auto [a, t, i] : vc)
        if (a >= k) vt.emplace_back(a, t, i);
    ranges::sort(vt, [](node& a, node& b) { return a.t < b.t; });
    int cnt = 0;
    for (auto [a, t, i] : vt) {
        if (x < t) break;
        cnt++, x -= t;
    }
    return cnt >= k;
}

vector<node> ans;
int main() {
    fast;
    int n, q; cin >> n >> q;
    for (int i = 1, a, t; i <= n; ++i)
        cin >> a >> t, vc.emplace_back(a, t, i);
    int l = 0, r = inf;
    while (l + 1 < r) {
        int mid = (l+r)>>1;
        if (check(mid, q)) l = mid, ans = vt;
        else r = mid;
    }
    cout << l << '\n' << l << '\n';
    for (int i = 0; i < l; ++i) cout << ans[i].id << ' ';
    return 0;
}