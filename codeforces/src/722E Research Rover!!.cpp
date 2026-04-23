//
// Created by Psy.C on 2026/4/23.
//
/**
add: 加法取模运算
del: 减法取模运算
inc: 返回两数相加取模的结果
inc1: 返回两数相减取模的结果
fac[N]: 阶乘数组
ifc[N]: 阶乘逆元数组
C(n,m): 计算组合数C(n,m)
ksm: 快速幂算法，计算a^b mod
n, m: 网格大小
k: 障碍物数量
s: 初始值
f[i][j]: 动态规划数组 到达第i个障碍物且某种属性为j的方案数
g[M]: 辅助数组

对每个障碍物进行处理
C(x-1+y-1, x-1)是从(1,1)到(x,y)的路径数
从f[i][0]和f[i][1]中减去直达到该点的路径数
枚举之前处理过的障碍物
如果障碍物j在障碍物i的左上方
计算从j到i的路径数
更新动态规划值
累加从当前障碍物到终点的贡献

添加无障碍物时的路径数
对奇数位置的g值取负
初始化总和
计算最终答案
用总路径数减去经过障碍物的路径数
输出结果（对总路径数求逆元作为概率）

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e6+7, M = 2007, mod = 1e9+7;

struct node {
    int x, y;
    bool operator<(const node &o) const {//按x坐标升序，相等时按y坐标升序
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
} a[M];
void add(int &x, int y) { x += y; if (x >= mod) x -= mod; }
void del(int &x, int y) { x -= y; if (x < 0) x += mod; }
int inc1(int x, int y) { return x - y + (x < y ? mod : 0); }

int fac[N], ifc[N];
int C(int n, int m) { return 1ll*fac[n]*ifc[m]%mod*ifc[n-m]%mod; }
int ksm(int a, int b) {
    int res = 1;
    while (b) {
        if (b&1) res = 1ll*res*a%mod;
        a = 1ll*a*a%mod;
        b >>= 1;
    }
    return res;
}

int n, m, k, s, f[M][M], g[M];
int main() {
    fast;
    fac[0] = fac[1] = ifc[0] = ifc[1] = 1;
    for (int i = 2; i <= N-7; ++i)
        fac[i] = 1ll*fac[i-1]*i%mod, ifc[i] = 1ll*ifc[mod%i]*(mod-mod/i)%mod;
    for (int i = 2; i <= N-7; ++i)
        ifc[i] = 1ll*ifc[i-1]*ifc[i]%mod;
    cin >> n >> m >> k >> s;
    for (int i = 1; i <= k; ++i) cin >> a[i].x >> a[i].y;
    sort(a + 1, a + k + 1);
    for (int i = 1; i <= k; ++i) {
        int x = a[i].x, y = a[i].y;
        del(f[i][0], C(x-1+y-1, x-1));
        del(f[i][1], C(x-1+y-1, x-1));
        for (int j = 1; j < i; ++j) {
            if (a[j].x > x || a[j].y > y) continue;
            int v = C(x - a[j].x + y - a[j].y, x - a[j].x);
            del(f[i][0], 1ll*f[j][0]*v%mod);
            for (int l = 1; l <= 20; ++l)
                del(f[i][l], 1ll*f[j][l]*v%mod), del(f[i][l], 1ll*f[j][l-1]*v%mod);
        }
        for (int j = 0; j <= 20; ++j)
            add(g[j], 1ll*C(n-x+m-y, n-x)*f[i][j]%mod);
    }
    add(g[0], C(n-1+m-1, n-1));
    for (int i = 1; i <= 20; i += 2) g[i] = inc1(0, g[i]);
    int sum = C(n-1+m-1, n-1), ans = 0;
    for (int i = 0; i <= 20; ++i) {
        add(ans, 1ll*s*g[i]%mod);
        del(sum, g[i]);
        s = (s + 1) / 2;
    }
    add(ans, sum);
    cout << 1ll*ans*ksm(C(n-1+m-1, n-1), mod-2)%mod;
    return 0;
}