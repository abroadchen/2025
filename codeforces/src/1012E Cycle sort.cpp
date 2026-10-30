//
// Created by Psy.C on 2026/10/30.
//

/**
真正学会的起点..
Hierholzer 算法遍历一条欧拉路径：
反复取 now 的最后一条出边 (fst, snd) 并弹出（pop_back）。
先递归走到 fst，返回后把边权 snd（即原始位置下标）压入当前路径 d[cnt]。
这样构造的 d[cnt] 是一条"交换链"：其中相邻位置的元素通过循环交换可以归位。路径长度 = 这条链上错位元素个数

读入 n、s，数组 a 存原值，b 存排序后的结果
对排序后数组去重，给每个不重复的值分配一个编号 1..tot（压缩值域）
对每个错位的位置 i（a[i] != b[i]），从 a[i] 的编号指向其目标值 b[i] 的编号，建立有向边，边权记录位置 i。边数就是最小交换次数 ans
对每个值编号，若有出边则以它为起点跑一遍 DFS，得到一条路径存进 d[cnt]，ans 累加路径长度（=总交换次数）
最小所需次数 ans 超过上限 s，无解，输出 -1。
计算可用"多余"次数 s-ans，用它去合并路径，t 为实际要合并的路径条数（不超过 cnt）
若多余次数不足 2（无法进行有效合并），直接按原路径条数输出：每组输出路径长度、路径上的位置序列
若 ${t\ge 2}$：进行路径合并压缩：
cnt++ 创建新路径 d[cnt]，把前 t 条路径的全部元素顺序拼接进去。
再 cnt++ 创建另一条短路径，把前 t 条路径的各自首元素逆序拼接（per 从大到小），作为收官交换。
输出合并后的路径组数 cnt-t（即 t+1 .. cnt 这些条），逐条输出
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= n; i++)
#define per(i,n) for (int i = n; i; i--)
#define ii pair<int, int>
using namespace std;

constexpr int N = 2e5+10;

vector<ii> to[N];
vector<int> d[N];
int cnt;
void dfs(int now) {
    while (!to[now].empty()) {
        auto [fst, snd] = to[now].back(); to[now].pop_back();
        dfs(fst);
        d[cnt].push_back(snd);
    }
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int a[N], b[N], tot, ans;
map<int,int> id;
int main() {
    fast;
    int n = rd(), s = rd();
    rep(i,n) b[i] = a[i] = rd();
    sort(b+1, b+n+1);
    rep(i,n) if (b[i] != b[i-1]) id[b[i]] = ++tot;
    rep(i,n) if (a[i] != b[i]) to[id[a[i]]].emplace_back(id[b[i]], i);
    rep(i,tot) if (!to[i].empty()) { cnt++; dfs(i); ans += d[cnt].size(); }
    if (s < ans) { cout << "-1\n"; return 0; }
    int t = min(cnt, s-ans);
    if (t < 2) {
        cout << cnt << '\n';
        rep(i,cnt) {
            cout << d[i].size() << '\n';
            for (auto j : d[i]) cout << j << ' ';
            cout << '\n';
        }
    } else {
        cnt++;
        rep(i,t) for (auto j : d[i]) d[cnt].push_back(j);
        cnt++;
        per(i,t) d[cnt].push_back(d[i][0]);
        cout << cnt-t << '\n';
        for (int i = t+1; i <= cnt; i++) {
            cout << d[i].size() << '\n';
            for (auto j : d[i]) cout << j << ' ';
            cout << '\n';
        }
    }
    return 0;
}