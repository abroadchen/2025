//
// Created by Psy.C on 2026/3/28.
//
/**
c[x][y] 表示在维度x上使用树状数组存储y方向的信息
add(x, i): 在位置(x,i)添加1
sum(x, i): 查询维度x上[1,i]范围内元素的和
g[j]: 存储在列j结束的Z型图案的起始坐标
l[i][j]: 第i行j列左边连续'z'的个数（包括自身）
r[i][j]: 第i行j列右边连续'z'的个数（包括自身）
从两边同时扫描，填充左右连续'z'计数
xx[i][j]: 从位置(i,j)沿右上对角线方向连续'z'的个数
从左下到右上遍历，计算对角线连续'z'
将每个'z'位置按照其所属的Z型图案结束列分组
j+r[i][j]-1 计算Z型图案的结束列位置

第一部分：添加节点到树状数组

遍历在列j结束的所有Z型图案
t = x + y：使用坐标和作为标识
将节点(y坐标)添加到对应的树状数组中
第二部分：计算贡献

p = min(l[i][j], xx[i][j])：当前位置能形成的Z型图案最大长度
l[i][j]: 水平方向可延伸长度
xx[i][j]: 对角线方向可延伸长度
sum(i + j, j) - sum(i + j, j - p): 查询范围内符合条件的图案数量

预处理：O(n*m)
主循环：O(nmlog²(m))
总体：O(nmlog²(m))
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 3005;

int c[N<<1][N], m;
void add(int x, int i) {
    for (; i <= m; i += i&-i) c[x][i]++;
}
int sum(int x, int i) {
    int res = 0;
    for (; i > 0; i -= i&-i) res += c[x][i];
    return res;
}
struct node { int x, y; };
vector<node> g[N];

int n, l[N][N], r[N][N], xx[N][N];
char s[N][N];
int main() {
    fast;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%s", s[i] + 1);
    for (int i = 1; i <= n; ++i)
        for (int j = 1, k = m; j <= m; ++j, --k) {
            if (s[i][j] == 'z') l[i][j] = l[i][j-1] + 1;
            if (s[i][k] == 'z') r[i][k] = r[i][k+1] + 1;
        }
    for (int j = 1; j <= m; ++j)
        for (int i = 1; i <= n; ++i) {
            if (s[i][j] == '.') continue;
            xx[i][j] = xx[i+1][j-1] + 1;
        }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (s[i][j] == 'z')
                g[j+r[i][j]-1].push_back({i, j});
    ll ans = 0;
    for (int j = m; j >= 1; --j) {
        for (auto &[x, y] : g[j]) {
            int t = x + y;
            add(t, y);
        }
        for (int i = 1; i <= n; ++i) {
            if (s[i][j] == '.') continue;
            int p = min(l[i][j], xx[i][j]);
            ans += sum(i + j, j) - sum(i + j, j - p);
        }
    }
    printf("%lld\n", ans);
    return 0;
}