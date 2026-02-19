//
// Created by Psy.C on 2026/2/19.
//
/**
vx[N], vy[N];           // 访问标记数组 左部节点i是否在当前DFS搜索路径中 右部节点j是否在当前DFS搜索路径中
lx[N], ly[N];            // 左右顶标 左部节点i的顶标值 右部节点j的顶标值
w[N][N];                 // 权重矩阵 第i个字符映射到第j个字符的收益（出现频次）
mx[N], my[N];            // 匹配数组 左部节点i匹配的右部节点 右部节点j匹配的左部节点
d;                       // 松弛变量
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 53, M = 2e6+1, inf = 1e9;

bool vx[N], vy[N];
int lx[N], ly[N], w[N][N], mx[N], my[N], d;
bool dfs(const int x, const int n) {//寻找从左部节点x出发的增广路径
    vx[x] = true;
    for (int y = 0; y < n; ++y) if (!vy[y]) {
        if (lx[x] + ly[y] == w[x][y]) {// 找到相等子图的边
            vy[y] = true;
            if (my[y] == -1 || dfs(my[y], n)) {//找到增广路或递归找到增广路
                mx[x] = y; my[y] = x;
                return true;
            }
        } else d = min(d, lx[x] + ly[y] - w[x][y]);//最小松弛量
    }
    return false;
}

void km(const int m, const int n) {
    memset(mx, -1, sizeof(mx));
    memset(my, -1, sizeof(my));
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            lx[i] = max(lx[i], w[i][j]);//每行最大权重值
    for (int k = 0; k < m; ++k) {
        memset(vx, false, sizeof(vx));
        memset(vy, false, sizeof(vy));
        d = inf;
        if (dfs(k, n)) continue;//找到匹配则继续
        //调整顶标
        for (int i = 0; i < m; ++i) if (vx[i]) lx[i] -= d;
        for (int i = 0; i < n; ++i) if (vy[i]) ly[i] += d;
        k--;//重新尝试当前节点
    }
}

int get(const char c) {
    if (c >= 'a' && c <= 'z') return c - 'a';//小写字母: 0-25
    return c - 'A' + 26;//大写字母: 26-51
}
char get(const int x) {
    if (x >= 0 && x < 26) return x + 'a';//0-25 -> a-z
    return x - 26 + 'A';//26-51 -> A-Z
}

int n, k;
char s1[M], s2[M];
int main() {
    fast;
    cin >> n >> k >> s1 >> s2;
    for (int i = 0; i < n; ++i) {
        const int x = get(s1[i]), y = get(s2[i]);
        w[x][y]++;//字符对出现次数作为权重
    }
    km(k, k);
    int ans = 0;
    for (int i = 0; i < k; ++i) ans += w[i][mx[i]];//总权重
    cout << ans << '\n';
    for (int i = 0; i < k; ++i) cout << get(mx[i]);
    return 0;
}