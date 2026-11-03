//
// Created by Psy.C on 2026/11/3.
//

/**
真正学会的起点..
node {x,y,z}：记录一次操作 (x,y,z)（三个下标构成等差数列）。
a[13]、b[13]：长度为 11（或 8）的 0/1 状态向量，作为 map 的 key。
mp：从某个状态映射到能把它消成全 0 的操作序列。
s：预处理表，用于 n 大时的快速转移
枚举合法操作三元组 (i,j,k)（k=2*j-i，等差数列，不超过 m）。
翻转这三个位置的 0/1，得到新状态记录进 mp（保留更短解）。
递归上限 up，防止解太长；回溯恢复翻转。
结果：对任意短状态，mp[state] 给出把它变全 0 的最小操作序列
针对长度为 11 的小窗口预计算所有可能"前半固定、后半变化"状态的最优消零方案，存入 s，供 n 大时使用
情形 1：n ≤ 11，直接小规模暴力
直接把整个数组下半段清零目标：能否消全 0 由 mp 查。
这里 b 应为全 0 状态（即把开头状态变成全 0）。
情形 2：n 较大，用预处理表逐窗口处理
从左往右滑窗：当前位 x[i] 为 1 时，用预处理表 s 找到消掉它的方案并记录下来、翻转对应位置，把 1 "往后推"。
尾部处理
对最后几位的残余用朴素三元翻转或长度 8 的小窗口 DFS 收尾消零
输出操作数及每个三元组
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;

constexpr int N = 1e6+5;

struct node { int x, y, z; };

map<vector<int>,vector<node>> mp;
vector<int> a(13);
void dfs(vector<node> v, int m, int up) {
    if (v.size() > up) return;
    mp[a] = v;
    rep(i,m) for (int j = i+1; j <= m; ++j) {
        int k = 2*j-i;
        if (k > m) continue;
        a[i]^=1, a[j]^=1, a[k]^=1;
        v.push_back({i,j,k});
        if (!mp.contains(a) || mp[a].size() > v.size()) dfs(v,m,up);
        v.pop_back();
        a[i]^=1, a[j]^=1, a[k]^=1;
    }
}

vector<int> b(13);
map<vector<int>,vector<node>> s;
void init() {
    for (int i = 1; i < 1<<6; i += 2) {//i 枚举某种奇数掩码
        rep(j,11) a[j] = i>>(j-1)&1;//构造 a 状态
        mp.clear(); dfs({},11,2);//求 mp
        vector<node> ans;
        for (int j = 0; j < 1<<6; ++j) {//枚举后半段掩码
            rep(k,11) {//构造 b: 前6位为0, 后5位取掩码
                if (k <= 6) b[k] = 0;
                else b[k] = j>>(k-7)&1;
            }
            if (mp.contains(b) && (mp.size() < ans.size() || ans.empty()))
                ans = mp[b];
        }
        s[a] = ans;//存"当状态为a时最好方案"
    }
}

int n, x[N];
vector<node> ans;
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> x[i];
    if (n <= 11) {
        rep(i,n) a[i] = x[i];
        dfs({}, n, n);
        if (!mp.contains(b)) { cout << "NO\n"; return 0; }
        cout << "YES\n" << mp[b].size() << '\n';
        for (auto p : mp[b])
            cout << p.x << ' ' << p.y << ' ' << p.z << '\n';
        return 0;
    }
    init();
    rep(i,11) a[i] = b[i] = 0;
    rep(i,n-10) {
        if (!x[i]) continue;
        rep(j,6) b[j] = x[i+j-1];
        for (auto p : s[b]) {
            ans.push_back({i+p.x-1,i+p.y-1,i+p.z-1});
            x[i+p.x-1]^=1, x[i+p.y-1]^=1, x[i+p.z-1]^=1;
        }
    }
    for (int i : {n-9,n-8}) if (x[i]) {
        ans.push_back({i,i+1,i+2});
        x[i]^=1, x[i+1]^=1, x[i+2]^=1;
    }
    rep(i,8) { a[i] = x[n-8+i]; b[i] = 0; }
    mp.clear(); dfs({},8,6);
    for (auto p : mp[b]) {
        ans.push_back({n-8+p.x,n-8+p.y,n-8+p.z});
        x[n-8+p.x]^=1, x[n-8+p.y]^=1, x[n-8+p.z]^=1;
    }
    cout << "YES\n" << ans.size() << '\n';
    for (auto p : ans)
        cout << p.x << ' ' << p.y << ' ' << p.z << '\n';
    return 0;
}