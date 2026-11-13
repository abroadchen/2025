//
// Created by Psy.C on 2026/11/13.
//

/**
真正学会的起点..
v[k] 存的是以 k 为根，深度限制为 d，权值增量 val 的所有操作。
树状数组 a[] 的下标表示深度，不是节点编号
标准树状数组。
配合差分技巧：在区间 [l, r] 加 y，等价于 add(l, y) 和 add(r+1, -y)；单点查询直接用 ask(x) 求前缀和
进入节点 k 时，把它的所有更新操作 (d, val) 施加到深度区间 [d, d+depth]（从当前深度 d 到 d+限制），用树状数组差分实现区间加。
查询答案：ans[k] = ask(d) 取当前深度 d 的前缀和，得到所有能覆盖到节点 k 的更新的累加值。
递归访问子树：深度逐层 +1，这样子树里的每个节点在查询时，用的深度就是自己的真实深度。
回溯撤销：离开节点 k 时，把刚才施加的操作全部撤销（反向 add），保证这些更新只在 k 的子树范围内生效，不影响其他分支
读入树的边，然后读入 m 个操作，全部挂在对应节点 v[k] 上。
从根开始 dfs(1, 0, 1) 一次遍历，边遍历边应用和撤销操作，得到每个节点的答案。
最后输出 n 个节点的最终权值。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
#define ll long long
#define ii pair<int,int>
using namespace std;

constexpr int N = 1e6+10;

int n;
ll a[N];//树状数组（维护"按深度"的差分和）
void add(int x, int y) { while (x <= n) { a[x] += y; x += x&-x; } }
ll ask(int x) {
    ll tot = 0;
    while (x) { tot += a[x]; x -= x&-x; }
    return tot;
}

vector<ii> v[N];
ll ans[N];
vector<int> e[N];
void dfs(int k, int fa, int d) {
    for(auto &[fst, snd] : v[k]) {
        add(d, snd);//在深度 [d, d+fst] 区间加 snd
        if (d+fst+1 <= n)
            add(d+fst+1, -snd);//区间右端+1 处减去，形成差分
    }
    ans[k] = ask(d);//查询当前深度 d 上的累计值，即为节点 k 的答案
    rep(i,e[k].size()) {
        if (e[k][i] == fa) continue;
        dfs(e[k][i], k, d+1);//递归子树，深度 +1
    }
    //回溯：撤销当前节点施加的更新，保证只影响自己的子树
    for(auto &[fst, snd] : v[k]) {
        add(d, -snd);
        if (d+fst+1 <= n)
            add(d+fst+1, snd);
    }
}

int main() {
    fast;
    cin >> n;
    for (int i = 1, x, y; i < n; i++) {
        cin >> x >> y; e[x].push_back(y); e[y].push_back(x);
    }
    int m; cin >> m;
    while (m--) {
        int k, d, val; cin >> k >> d >> val;
        v[k].emplace_back(d,val);
    }
    dfs(1,0,1);
    for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
    return 0;
}