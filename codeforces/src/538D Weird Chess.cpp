//
// Created by Psy.C on 2026/3/5.
//
/**
mp[N][N]: 输入的原始地图
a[N][N]: 构造的目标地图
vis[N][N]: 标记数组，记录某些位置是否被覆盖
n: 地图边长
设置a[n][n] = 'o'（中心位置为'o'）
设置每行的结束符（防止字符串越界）

遍历原图中所有'o'的位置(i,j)
遍历原图中所有'.'的位置(x,y)
在目标图a中对应位置设置'.'：a[n+x-i][n+y-j] = '.'
这里实现了相对位置的变换

遍历原图中所有'o'的位置(i,j)
遍历原图中所有'x'的位置(x,y)
如果目标图a中对应位置也是'x'，则标记vis[x][y]为true
这样标记出那些不需要保留的'x'

检查原图中是否有'x'没有被标记（即没有被合理处理）
如果有未被标记的'x'，输出"NO"并退出
否则输出"YES"
输出构造好的目标图a
(n<<1)-1 即 2*n-1，输出扩展后的地图
puts(a[i]+1) 输出字符串（跳过第0列）

 */
#include <bits/stdc++.h>
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;

int read() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

constexpr int N = 110;
char mp[N][N], a[N][N];
bool vis[N][N];
int n;
int main() {
    memset(a, 'x', sizeof(a));
    n = read();
    rep(i,n) scanf("%s", mp[i]+1);//让列从1开始
    a[n][n] = 'o';
    rep(i,(n<<1)-1) a[i][n<<1] = '\0';
    rep(i,n) rep(j,n) if (mp[i][j] == 'o')
        rep(x,n) rep(y,n) if (mp[x][y] == '.')
            a[n+x-i][n+y-j] = '.';
    rep(i,n) rep(j,n) if (mp[i][j] == 'o')
        rep(x,n) rep(y,n) if (mp[x][y] == 'x' && a[n+x-i][n+y-j] == 'x')
            vis[x][y] = true;
    bool flag = true;
    rep(i,n) rep(j,n) if (mp[i][j] == 'x' && !vis[i][j]) {
        flag = false; break;
    }
    if (!flag) return puts("NO"), 0;
    puts("YES");
    rep(i,(n<<1)-1) puts(a[i]+1);
    return 0;
}