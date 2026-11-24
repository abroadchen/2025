//
// Created by Psy.C on 2026/11/24.
//

/**
真正学会的起点..
cntb = 目标 b 中不同元素的种数（用 !cb[b[i]]++ 实现：某值第一次出现才 +1）。cb[val] 记录每种值需要的数量
典型的滑动窗口：j 单调右移，窗口 [i, j] 内包含目标所有元素即可（不必多算，只要求每个目标值数量≥cb）。
若窗口满足 → 计算"要删的最少个数" tot：
(i-1)%k：为对齐整除 k 而前段删除数（把窗口起点之前的部分删到能被 k 整除）。
max(0, j-i+1-k)：为凑成整段 k 而删去窗口末尾多余部分。
条件 m-tot ≥ n*k：删除后还能留下 n 段完整的、每段长 k（共 n*k 个）的序列 → 该方案可行，更新 ans。
最后把 a[i] 从计数里退出去（cnt -= c[a[i]]-- == cb[a[i]]）。
一句话：在能在不破坏分段的前提下，最少删多少个数才能让剩下序列包含所有目标元素
重跑一遍滑窗，当找到 tot == ans 的那个最优窗口时输出方案：
前置删除部分：(i-1)/k*k+1 到 i-1，即窗口起点之前的、用来对齐整除 k 而删掉的下标。
窗口内删除部分：扫描 [i..j]，凡是"数量已经超过目标 cb 的"多余下标，记入 t，取前 j-i+1-k 个删掉。
输出所有要删的下标后直接 return 0（只.ned构造一个最优方案）。
若第一遍 ans 无解（inf），输出 -1

a[j]：当前处理的第 j 个元素的值。
c[a[j]]：该值在当前窗口内已经出现的次数（数组 c 是统计桶）。
++c[a[j]]：前缀自增，先把 c[a[j]] 加 1，然后整个表达式的值就是加完之后的新值。
cb[a[j]]：该值在目标数组 b 里需要的次数
把某个值的窗口计数 +1，然后判断"加完后是否正好达到目标数量"
c[a[i]]--：后缀自减，用旧值比较，再减 1。
判断"减之前是否恰好等于目标数量"——是则说明这个值从"刚好满足"变成"不足"，cnt 减 1
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;i++)
using namespace std;

constexpr int N = 5e5+10, inf = 1e9;
int m, k, n, s, a[N], b[N], cntb, cb[N], cnt, c[N], ans = inf;
vector<int> v[N], pt;
int main() {
    fast;
    cin >> m >> k >> n >> s;
    rep(i,m) cin >> a[i], v[a[i]].push_back(i);
    rep(i,s) cin >> b[i], cntb += !cb[b[i]]++;
    for (int i = 1, j = 0; i <= m; i++) {
        while (j < m && cnt < cntb) ++j, cnt += ++c[a[j]] == cb[a[j]];
        if (cnt == cntb) {
            int tot = (i-1)%k + max(0, j-i+1-k);
            if (m-tot >= n*k) ans = min(ans, tot);
        }
        cnt -= c[a[i]]-- == cb[a[i]];
    }
    if (ans == inf) return cout << "-1\n", 0;
    cout << ans << '\n'; memset(c, 0, sizeof c); cnt = 0;
    for (int i = 1, j = 0; i <= m; i++) {
        while (j < m && cnt < cntb) ++j, cnt += ++c[a[j]] == cb[a[j]];
        if (cnt == cntb) {
            int tot = (i-1)%k + max(0, j-i+1-k);
            if (tot == ans) {
                for (int p = (i-1)/k*k+1; p < i; p++) pt.push_back(p);//窗口前的冗余段
                memset(c, 0, sizeof c);
                vector<int> t;
                for (int p = i; p <= j; p++)
                    if (++c[a[p]] > cb[a[p]]) t.push_back(p);//窗口内超出目标数量的位置
                for (int p = 0; p < j-i+1-k; p++) pt.push_back(t[p]);//窗口内要删的前 j-i+1-k 个
                for (int p : pt) cout << p << ' ';
                return 0;
            }
        }
        cnt -= c[a[i]]-- == cb[a[i]];
    }
    return 0;
}