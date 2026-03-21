//
// Created by Psy.C on 2026/3/21.
//
/**
平均情况：O(m×Δ)，其中m为边数，Δ为最大度数
空间复杂度：O(Δ×n)，用于存储颜色-顶点矩阵
x^y^c[id] - 在三个颜色中找出不同于另外两个的颜色
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5, M = 2e3+5;

struct node { int u, v; } s[N];///存储边信息

int mat[M][M];///颜色和顶点的占用关系
int query(int x) {
    int i = 1;
    while (mat[i][x]) i++;//顶点x上第一个未被占用的颜色
    return i;
}

int c[N];
void dfs(int id, int x, int y) {
    int u = s[id].u, v = s[id].v, ID;
    if (mat[c[id]][u] == id)//边id当前占用的是u端点
        ID = mat[x][u], mat[c[id]][u] = 0;//获取x颜色在u上的边，释放当前占用
    else ID = mat[x][v], mat[c[id]][v] = 0;//获取x颜色在v上的边，释放当前占用
    mat[x][u] = mat[x][v] = id;//将边id分配给颜色x
    c[id] = x;//更新边id的颜色
    if (ID) dfs(ID, y, x);//如果存在冲突，继续处理
}

void get(int u, int v, int id) {
    int x = query(u), y = query(v), ID = 0;//为u和v找到可用颜色
    if (x < y) ID = mat[x][v], c[id] = x;//选择较小颜色，记录冲突边
    else ID = mat[y][u], c[id] = y;
    mat[c[id]][u] = mat[c[id]][v] = id;
    if (ID) dfs(ID, x^y^c[id], c[id]);
}

int x, y, n, m;
int main() {
    fast;
    cin >> x >> y; n = x + y;//读入二分图左右部分的顶点数
    cin >> m;//读入边数
    for (int i = 1, t; i <= m; ++i) {
        cin >> s[i].u >> t;
        s[i].v = t + x;//将右部顶点编号调整为全局编号
    }
    for (int i = 1; i <= m; ++i) get(s[i].u, s[i].v, i);//为每条边分配颜色
    int ans = 0;
    for (int i = 1; i <= m; ++i) ans = max(ans, c[i]);//最大使用颜色数
    cout << ans << '\n';//颜色总数
    for (int i = 1; i <= m; ++i) cout << c[i] << ' ';//每条边的颜色
    return 0;
}