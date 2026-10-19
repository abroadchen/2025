//
// Created by Psy.C on 2026/10/18.
//
/**
递归按二进制从低到高处理。
奇数位：两个选择——把这个奇数值上取整（+1）或下取整（-1）再右移，产生两条路径。
每条路径末尾追加 ±2^dep 作为"结果链"的一个项。
返回步数更短的分支
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
#define vi vector<int>
#define sz(x) ((int)(x).size())
using namespace std;

constexpr int N = 2e5+5, inf = 114514;

//排序 + 去重。用 -inf（114514）做哨兵避免越界
void get(vi &a) {
    ranges::sort(a);
    vi b; a.push_back(-inf);
    rep(i,a.size()-1) if (a[i] != a[i+1]) b.push_back(a[i]);
    a.swap(b);
}
vi dfs(int dep, vi &a) {
    if (dep > 20) return vi(0);
    get(a);
    int f = 0;
    for (int x : a) f |= x&1;//检测是否存在奇数
    if (!f) {//全是偶数 → 全体右移1再递归
        for (int &x : a) x >>= 1;
        return dfs(dep+1, a);
    }
    //有奇数 → 拆分奇偶两派，各自尝试 +1 / -1 后右移
    vi s1, s2;
    for (int x : a) if (x&1) s1.push_back((x-1)>>1); else s1.push_back(x>>1);
    for (int x : a) if (x&1) s2.push_back((x+1)>>1); else s2.push_back(x>>1);
    vi a1 = dfs(dep+1, s1), a2 = dfs(dep+1, s2);
    a1.push_back(1<<dep), a2.push_back(-(1<<dep));//记录本次操作的 ±2^dep
    if (sz(a1) < sz(a2)) return a1;
    return a2;
}

int n;
vi a;
int main() {
    fast;
    cin>>n;
    for (int i = 1, x; i <= n; ++i) {
        cin>>x; a.push_back(x);
    }
    vi ans = dfs(0, a);
    cout << sz(ans) << '\n';//输出最少操作数
    for (int x : ans) cout << x << ' ';//输出每次的操作量(±2^k)
    return 0;
}