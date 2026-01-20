//
// Created by Psy.C on 2026/1/20.
//
/**
* 全局变量k：约束参数
w1[11], w2[11]：工作数组（大小限制为10以内）
dfs函数：递归处理矩形区域
s：原始矩阵，t：转置矩阵
[u,d]×[l,r]：当前处理的矩形区域
 *
*如果宽度大于高度，交换s和t递归调用（优化递归）
如果只有一行，检查单个元素是否符合条件
 *
*w1[p-1] 和 w1[p]：相邻约束的边界差异
w2[k-p] 和 w2[k-p-1]：对称约束的边界差异
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 2505
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;

int b[N][N];
int get(const int u, const int d, const int l, const int r) {//矩形区域[u,d]×[l,r]的元素和
    return b[d][r] - b[u-1][r] - b[d][l-1] + b[u-1][l-1];
}

int k, w1[11], w2[11];
ll dfs(char **s, char **t, const int u, const int d, const int l, const int r) {
    if (r - l + 1 > d - u + 1) return dfs(t, s, l, r, u, d);
    if (u == d) {
        if (s[u][l] == '0' && k == 0) return 1;
        if (s[u][l] == '1' && k == 1) return 1;
        return 0;
    }
    ll ans = 0;
    const int mid = (u + d) >> 1;//垂直中线
    for (int i = u; i <= d; ++i) for (int j = l; j <= r; ++j) {//构建当前区域的二维前缀和数组
        b[i][j] = s[i][j] - '0';
        b[i][j] += b[i-1][j] + b[i][j-1] - b[i-1][j-1];
    }
    for (int i = l; i <= r; ++i) {//遍历所有可能的列范围[i,j]
        for (int j = 0; j <= k; ++j) w1[j] = u, w2[j] = d;//初始化边界指针w1和w2
        for (int j = i; j <= r; ++j) {//调整边界指针以满足约束条件
            for (int p = 0; p <= k; ++p) {
                while (get(w1[p], mid, i, j) > p) w1[p]++;//上半部分和
                while (get(mid+1, w2[p], i, j) > p) w2[p]--;
            }
            for (int p = 0; p <= k; ++p) {//满足条件的子矩阵数量
                const int tu = (p ? w1[p-1] : mid + 1) - w1[p],//上半部分有效行数
                td = w2[k-p] - (p != k ? w2[k-p-1] : mid);
                ans += tu * td;//组合数
            }
        }
    }
    //清空前缀和数组
    for (int i = u; i <= d; ++i) for (int j = l; j <= r; ++j) b[i][j] = 0;
    ans += dfs(s, t, u, mid, l, r);//分治递归处理上下两半区域
    ans += dfs(s, t, mid+1, d, l, r);
    return ans;
}


int main() {
    fast;
    int n, m; cin >> n >> m >> k;
    char s[N][N], t[N][N], *ss[N], *tt[N];
    string str;
    rep(i,n) { cin >> str; strcpy(s[i] + 1, str.data()); }
    rep(i,m) rep(j,n) t[i][j] = s[j][i];//构建s的转置矩阵t
    rep(i,n) ss[i] = s[i];//设置指针数组用于递归调用
    rep(i,m) tt[i] = t[i];
    cout << dfs(ss, tt, 1, n, 1, m) << '\n';
    return 0;
}