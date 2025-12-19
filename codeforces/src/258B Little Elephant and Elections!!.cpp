//
// Created by Psy.C on 2025/12/19.
//
/*
 *数位DP函数：统计满足条件的数字个数
 *step: 当前处理到第几位
 *r: 还需要多少个4或7
 *lim: 是否受到上界限制
 *
 *组合DFS函数：计算排列组合
 *step: 剩余步骤数
 *r: 剩余个数
 *mul: 当前的乘积
 *
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 15
#define mod 1000000007
using namespace std;

void add(int& x, const int y) {
    x += y;
    if (x >= mod) x -= mod;
}

int f[N][N], d[N];//f:记忆化数组, d:存储数字的各位
int dfs(const int step, const int r, const int lim) {
    if (step == 0) return r == 0;//还需要0个4或7 处理完所有位数
    if (!lim && ~f[step][r]) return f[step][r];//不受限制且已计算过
    const int x = lim ? d[step] : 9;//当前位的最大值
    int res = 0;//结果计数器
    for (int i = 0; i <= x; ++i) {//枚举当前位可以填的数字(0-9)
        if (i == 4 || i == 7) {
            if (r == 0) continue;//如果不需要4或7了，跳过
            add(res, dfs(step - 1, r - 1, lim && i == x));//选择这个4或7，递归处理下一位
            continue;
        }
        res += dfs(step - 1, r, lim && i == x);//不是4或7的情况，直接递归 是否在当前位达到了上限
    }
    if (!lim) f[step][r] = res;
    return res;
}

int g[N];//存储每种情况的计数
int dfs2(const int step, const int r, const ll mul) {
    if (step == 0) return static_cast<int>(mul);
    int res = 0;
    for (int i = 0; i <= r; ++i) if (g[i]) {//如果g[i]>0
        g[i]--;//使用一个g[i]
        add(res, dfs2(step - 1, r - i, mul * (g[i] + 1) % mod));//递归计算，更新乘积
        g[i]++;//回溯，恢复g[i]
    }
    return res;
}


int main() {
    fast;
    memset(f,-1,sizeof(f));
    int m, len = 0; cin>>m;
    while (m) d[++len] = m % 10, m /= 10;//将m的各位数字存储到d数组中（低位在前）
    for (int i = 0; i <= len; ++i) g[i] = dfs(len, i, 1);//从最高位开始，需要i个4或7
    g[0]--;//减去全0的情况
    int ans = 0;
    for (int i = 1; i <= len; ++i) add(ans,
        static_cast<int>(1ll * g[i] * dfs2(6, i - 1, 1) % mod));
    cout << ans << '\n';
    return 0;
}