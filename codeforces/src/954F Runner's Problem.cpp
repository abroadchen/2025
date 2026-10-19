//
// Created by Psy.C on 2026/10/19.
//
/**
定义了 3×3 转移矩阵。reset() 给出一个允许相邻相同的满转移（1→1,1→2;2→1→3;3→2→3），这其实是完整转移基，后面会按禁用情况把某行清零。

3×3 表示三状态（值 1/2/3）。矩阵乘法取模 1e9+7。ksm 做矩阵快速幂（用于把"一个长度为 len 的区间段"压缩成转移幂）
读入 n 个约束：每个给一个值 v 和一个区间 [L,R]（在区间内该位置上不允许填 v，或类似限制）。把所有端点（含 L-1、R、1、m）收集、排序、去重做离散化
用差分数列 num[值][端点下标] 标记每个值在哪些离散段内被禁用（前缀和即当前该值是否禁用）
初始状态是位置 1 = 值 2（ans.v[2][1]=1 表示第一维状态2）。从左往右每个离散段：

长度 len = ob[i]-ob[i-1]。
构造本段转移矩阵 x，把本段被禁用的值 j 的那一行清零（不能落在该状态）。
用矩阵快速幂 x^len 处理该段连续 len 个位置。
与总答案矩阵乘起来。
最终读取 ans.v[2][1] 输出方案数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
#define int long long
using namespace std;

constexpr int N = 2e5+5, mod = 1e9+7;

struct mtx {
    int v[5][5];
    void clear() { rep(i,1,3) rep(j,1,3) v[i][j] = 0; }
    void init() { clear(); v[1][1] = v[2][2] = v[3][3] = 1; }
    void reset() {
        clear();
        v[1][1] = v[1][2] = 1;
        v[2][1] = v[2][2] = v[2][3] = 1;
        v[3][2] = v[3][3] = 1;
    }
    mtx operator*(const mtx b) const {
        mtx ret{};
        rep(i,1,3) rep(j,1,3) rep(k,1,3)
            ret.v[i][j] = (ret.v[i][j]+v[i][k]*b.v[k][j]%mod)%mod;
        return ret;
    }
};
mtx ksm(mtx a, int b) {
    mtx ret{}; ret.init();
    while (b) {
        if (b&1) ret=ret*a;
        a=a*a;
        b>>=1;
    }
    return ret;
}

int n, m, v[N], L[N], R[N], ob[N], cnt, num[5][N], cur[5];
signed main() {
    fast;
    cin>>n>>m;
    rep(i,1,n) {
        cin >> v[i] >> L[i] >> R[i];
        ob[++cnt] = L[i] - 1; ob[++cnt] = R[i];
    }
    ob[++cnt] = 1; ob[++cnt] = m;
    sort(ob+1, ob+1+cnt);
    cnt = unique(ob+1, ob+cnt+1) - ob - 1;
    rep(i,1,n) {
        int l = lower_bound(ob+1, ob+1+cnt, L[i]) - ob;
        int r = lower_bound(ob+1, ob+1+cnt, R[i]) - ob;
        num[v[i]][l]++;
        num[v[i]][r+1]--;
    }
    mtx ans{}; ans.v[2][1] = 1;
    rep(i,2,cnt) {
        int len = ob[i] - ob[i-1];//当前段长度
        mtx x{}; x.reset();//起始为满转移
        rep(j,1,3) {
            cur[j] += num[j][i];//累积差分 → 该段值j是否禁用
            if (cur[j] != 0) {//若值j在本段禁用
                x.v[j][1] = 0; x.v[j][2] = 0; x.v[j][3] = 0;//禁止转移到状态j
            }
        }
        x = ksm(x, len);//该段长 len 的转移矩阵 = x^len
        ans = x*ans;//累乘到总答案
    }
    cout << ans.v[2][1] << '\n';
    return 0;
}