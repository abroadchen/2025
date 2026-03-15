//
// Created by Psy.C on 2026/3/15.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 405, M = 1e5+5;

int mod;
int ksm(int x, int y) {
    if (y == 0) return 1;//指数为0，返回1
    int t = ksm(x, y/2);//递归计算x^(y/2)
    if (y%2 == 0) return 1ll*t*t%mod;
    return 1ll*t*t%mod*x%mod;
}

void add(int& x, int y) {
    x += y;
    if (x >= mod) x -= mod;
}

int fa[M];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int a[N][N];//矩阵
///计算n×n矩阵的行列式
int get(int n) {
    int ans = 1;//初始化结果为1
    for (int i = 1; i <= n; ++i) {//对每一行进行高斯消元
        for (int j = i + 1; j <= n; ++j) if (a[j][i]) {//寻找主元
            swap(a[i], a[j]);//交换第i行和第j行
            ans = mod - ans;//改变符号
        }
        int inv = ksm(a[i][i], mod - 2);//计算对角元素的逆元
        for (int j = i + 1; j <= n; ++j) if (a[j][i]) {//消元
            int t = 1ll*a[j][i]*inv%mod;//计算倍数
            for (int k = i; k <= n; ++k)//对该行每个元素进行消元
                add(a[j][k], mod - 1ll*a[i][k]*t%mod);
        }
    }
    for (int i = 1; i <= n; ++i) ans = 1ll*ans*a[i][i]%mod;//主对角线元素乘积
    return ans;
}
///n,m为网格大小，num存储位置编号，tot计数器，g映射数组
int n, m, num[N][N], tot, g[M];
char s[N][N];//网格字符

///解决特定颜色的方案数，op表示奇偶性
int solve(int op) {
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= m; ++j) {
            if ((i+j)%2 == op) fa[num[i][j]] = num[i][j];//如果满足条件，设置自己为根
            else fa[num[i][j]] = 0;
        }
    for (int i = 1; i <= n; ++i)//处理网格中的每个格子
        for (int j = 1; j <= m; ++j) {
            if ((i+j)%2 == op) {
                if (s[i][j] == '\\') {
                    int x = find(num[i][j]), y = find(num[i-1][j-1]);//找两个点的根
                    if (x == y) return 0;//在同一集合
                    fa[x] = y;//合并
                }
            } else {
                if (s[i][j] == '/') {
                    int x = find(num[i-1][j]), y = find(num[i][j-1]);
                    if (x == y) return 0;
                    fa[x] = y;
                }
            }
        }
    int cnt = 0;//连通块
    for (int i = 1; i <= tot; ++i)//给每个连通块分配新编号
        if (fa[i] == i) g[i] = ++cnt;
    //连通块太多
    if (cnt > 200) return 0; memset(a, 0, sizeof(a));//清空矩阵
    //构建基尔霍夫矩阵
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            if ((i+j)%2 == op) {
                if (s[i][j] == '*') {
                    //获取连通块编号
                    int x = g[find(num[i][j])], y = g[find(num[i-1][j-1])];
                    if (x != y) {
                        add(a[x][x], 1); add(a[y][y], 1);//增加度数
                        add(a[x][y], mod - 1); add(a[y][x], mod - 1);//减少边权
                    }
                }
            } else {
                if (s[i][j] == '*') {
                    int x = g[find(num[i-1][j])], y = g[find(num[i][j-1])];
                    if (x != y) {
                        add(a[x][x], 1); add(a[y][y], 1);
                        add(a[x][y], mod - 1); add(a[y][x], mod - 1);
                    }
                }
            }
        }
    return get(cnt - 1);//生成树数量
}

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int main() {
    fast;
    rd(n), rd(m), rd(mod);
    for (int i = 1; i <= n; ++i) scanf("\n%s", s[i] + 1);
    for (int i = 0; i <= n; ++i)//给每个位置编号
        for (int j = 0; j <= m; ++j) num[i][j] = ++tot;
    int ans = solve(0); add(ans, solve(1));//分别计算两种颜色的方案数并相加
    cout << ans << '\n';
    return 0;
}