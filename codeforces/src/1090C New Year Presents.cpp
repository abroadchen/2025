//
// Created by Psy.C on 2026/11/16.
//

/**
真正学会的起点..
s[i] 第 i 个集合，元素存 unordered_set。
m：所有集合元素总数。
d[i]：集合下标数组
d 按集合大小升序排列：d[1] 最小、d[n] 最大
num[i]：第 i 个"槽"（按数组下标、从大到小分配）应有的元素数。
含义：总共 m 个元素要尽量均匀地分到 n 个集合，大的集合分多一点（大集合 d[n] 对应更大的 num）。
直观：i%n 越小（i 越大）对应的 num 越接近最大，即"越大的集合，期望 size 越大"。
这本质是"把 m 分成 n 份，尽量均匀，盈余部分给靠前的槽"
st 初始 = 最大集合 s[d[n]]，挖掉其中也出现在最小集合 s[d[1]] 里的元素。
即 st = "只在最大集合、不在最小集合"的元素集合——这些元素是可安全搬动的候选，搬动不会让最小集合重复
l 指向当前最小的不达标集合，r 指向当前最大的超规模集合
把 r 左移（--r），重新初始化 st 为新的大集合中、不在当前最小集合里的元素
把 l 右移，并维护 st：把新小集合里也出现在大集合的元素加进候选，把不在新小集合的元素从 st 里清掉
从 st 里取一个候选元素 z，记录操作"从大集合 d[r] 把 z 移到小集合 d[l]"，同时在数据结构中执行移动，并把这个元素从候选中移除。
循环到 l >= r 结束
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e5+5;

struct node { int x, y, z; };
int n, x, m, d[N], y, num[N], l, r;
unordered_set<int> s[N], st;
vector<node> v;
int main() {
    fast;
    cin >> n >> x;
    for (int i = 1; i <= n; i++) {
        cin >> x; m += x; d[i] = i;
        while (x--) cin >> y, s[i].insert(y);
    }
    sort(d+1, d+n+1,[&](int u, int v) {
        return s[u].size() < s[v].size();
    });
    for (int i = 0; i < m; i++) num[n-i%n]++;
    l = 1, r = n; st = s[d[n]];
    for (int i : s[d[n]]) if (s[d[1]].contains(i)) st.erase(i);
    while (l < r) {
        if ((int)s[d[r]].size() == num[r]) {
            if (l >= --r) break;
            st = s[d[r]];
            for (int i : s[d[r]]) if (s[d[l]].contains(i)) st.erase(i);
            continue;
        }
        if ((int)s[d[l]].size() == num[l]) {
            for (int i : s[d[l]]) if (s[d[r]].contains(i)) st.insert(i);
            if (++l >= r) break;
            for (int i : s[d[l]]) if (st.contains(i)) st.erase(i);
            continue;
        }
        int z = *st.begin(); v.push_back({d[r],d[l],z});
        s[d[r]].erase(z), s[d[l]].insert(z), st.erase(z);
    }
    cout << v.size() << '\n';
    for (auto i : v) cout << i.x << ' ' << i.y << ' ' << i.z << '\n';
    return 0;
}