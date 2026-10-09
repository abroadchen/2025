//
// Created by Psy.C on 2026/10/9.
//
/**
一棵以 1 为根的完全二叉树，共
n
n 个节点（叶子在较深层）。
每条边有边权：对节点
i
i：
ls[i] =
i
i 到左孩子
2
i
2i 的边权；
rs[i] =
i
i 到右孩子
2
i
+
1
2i+1 的边权。
读入：对
i
=
2..
n
i=2..n，若
i
i 是奇数(右孩子)则读 rs[i>>1]，若是偶数(左孩子)则读 ls[i>>1]
先递归到叶子，再从叶子向上合并。

三种节点情况：

情况 1 —— 叶子 now<<1 > n
叶子到它自己距离为 0，v = {0}
情况 2 —— 只有左孩子 now<<1 == n
v[now] = {0} ∪ {ls[now] + v[left]}：距离 0（到自身）+ 到左子树所有点的距离
情况 3 —— 两个孩子都有
这是归并排序：左子树距离 + ls[now] 与右子树距离 + rs[now] 合并成有序表。因为左右子树的 v 本身是升序的，加常数后仍有序，用双指针归并能保证 v[now] 升序。
然后对每个节点建前缀和 s[now]
s[now][i] = v[now][0..i] 前缀和，方便区间求和 O(1)。
结论：v[now] 是从节点 now 出发，能到达的所有节点（now 的整棵子树）的距离的升序表（包含距离 0）。s 是对应前缀和
在 v[now] 里二分找第一个 > mx 的位置，id 是最后一个 ≤ mx 的下标。
对每个可到达的点，算 mx - 距离 并求和 = (id+1)*mx - 前缀和。
返回这些"剩余能量"的总和。这显然是某种DP贡献：每个点最多走 mx 距离投入，能留下 mx-实际距离 的“余量”
每个查询给节点 a 和"预算/能力" h（比如最多走总距离 h）。
初始：在 a 自己的子树内统计 calc(a, h)。
然后逐层向上走到根：
每次走到父节点，先减去走到父节点消耗的边权（ls/rs）。
若剩余 h ≤ 0 停止。
calc（父节点本身在 a^1 兄弟子树）加上兄弟子树的贡献：h + calc(a^1, 剩余预算 - 到兄弟的边权)。
注意 a^1 即当前节点的兄弟（若 a 是左孩子则兄弟是右孩子，反之亦然）。
这里 h 是已经走到父节点后剩余的预算，再 + ... 累积。
这样累加出最终答案
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e6+5;

int n;
vector<ll> v[N], s[N];
ll ls[N], rs[N];
void dfs(int now) {
    if (now<<1 <= n) dfs(now<<1);
    if ((now<<1|1) <= n) dfs(now<<1|1);
    if (now<<1 > n) {
        v[now].push_back(0);
        ll ans = 0;
        for (auto i : v[now]) s[now].push_back(ans+=i);
        return;
    }
    if (now<<1 == n) {
        v[now].push_back(0);
        for (auto i : v[now<<1]) v[now].push_back(ls[now]+i);
        ll ans = 0;
        for (auto i : v[now]) s[now].push_back(ans+=i);
        return;
    }
    vector<ll>& a = v[now], &l = v[now<<1], &r = v[now<<1|1]; a.push_back(0);
    int i = 0, j = 0;
    while (i < l.size() && j < r.size()) {
        if (l[i]+ls[now] <= r[j]+rs[now]) a.push_back(l[i]+ls[now]), i++;
        else a.push_back(r[j]+rs[now]), j++;
    }
    while (i < l.size()) a.push_back(l[i]+ls[now]), i++;
    while (j < r.size()) a.push_back(r[j]+rs[now]), j++;
    ll ans = 0;
    for (auto t : v[now]) s[now].push_back(ans+=t);
}

ll calc(int now, ll mx) {
    if (mx < 0 || now > n) return 0;
    int id = lower_bound(v[now].begin(), v[now].end(), mx) - v[now].begin() - 1;
    if (id < 0) return 0;
    return mx*(id+1) - s[now][id];
}

int m;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 2; i <= n; ++i) {
        if (i&1) cin >> rs[i>>1];
        else cin >> ls[i>>1];
    }
    dfs(1);
    while (m--) {
        int a, h; cin >> a >> h;
        ll ans = calc(a, h);
        for (; a > 1; a>>=1) {
            h -= (a&1) ? rs[a>>1] : ls[a>>1];
            if (h <= 0) break;
            ans += h + calc(a^1, h-((a&1)?ls[a>>1]:rs[a>>1]));
        }
        cout << ans << '\n';
    }
    return 0;
}