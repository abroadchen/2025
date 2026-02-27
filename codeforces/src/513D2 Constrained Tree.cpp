//
// Created by Psy.C on 2026/2/27.
//
/**
遍历所有以l为起点的约束
snd为1表示"LEFT"约束，snd为0表示"RIGHT"约束
对于LEFT约束：更新R为min(R, fst-1)
对于RIGHT约束：更新L为max(L, fst)
更新树状数组：减少l的计数，增加fst的计数

从两端向中间搜索
如果位置L的前缀和为0（表示该位置没有被区间覆盖），则：
递归处理[l+1, L]区间
将l加入结果
递归处理[L+1, r]区间
对R也做类似的检查

读入n（序列长度）和m（约束数量）
读入每个约束[a, b, direction]
如果b <= a，输出"IMPOSSIBLE"
根据方向('L'或'R')添加约束到v[a]
更新树状数组：在a位置+1，在b位置-1（区间标记）
调用DFS处理整个区间[1, n]
输出结果序列
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;

template<class T, class S>
bool maxx(T& a, S b) {
    return a < b ? a = b, true : false;
}
template<class T, class S>
bool minn(T& a, S b) {
    return a > b ? a = b, true : false;
}

constexpr int N = 1e6+1;

struct node {
    int a[N];
    void modify(const int x, const int v) {
        for (int i = x; i < N; i += i&-i)
            a[i] += v;
    }
    int sum(const int x) const {
        int ans = 0;
        for (int i = x; i; i -= i&-i)
            ans += a[i];
        return ans;
    }
} bit;

vector<int> ans;//结果序列
vector<ii> v[N];//约束条件
void dfs(const int l, const int r) {
    if (l > r) return;
    if (l == r) { ans.push_back(l); return; }
    int L = l, R = r;
    for (auto&[fst, snd] : v[l]) {
        if (snd) minn(R, fst - 1);
        else maxx(L, fst);
        bit.modify(l, -1);
        bit.modify(fst, 1);
    }
    for (; L <= R; ++L, --R) {
        if (!bit.sum(L)) {
            dfs(l + 1, L);
            ans.push_back(l);
            dfs(L + 1, r);
            return;
        }
        if (!bit.sum(R)) {
            dfs(l + 1, R);
            ans.push_back(l);
            dfs(R + 1, r);
            return;
        }
    }
    cout << "IMPOSSIBLE\n";
    exit(0);
}

int n, m;
char s[10];
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1, a, b; i <= m; ++i) {
        cin >> a >> b >> s;
        if (b <= a) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
        if (s[0] == 'L') v[a].emplace_back(b, 0);
        else v[a].emplace_back(b, 1);
        bit.modify(a, 1);
        bit.modify(b, -1);
    }
    dfs(1, n);
    for (const auto& t : ans) cout << t << ' ';
    cout << '\n';
    return 0;
}