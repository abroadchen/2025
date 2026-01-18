//
// Created by Psy.C on 2026/1/18.
//

#include <iostream>
#include <algorithm>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int dir[][4] = {
    {-1,0,1,0},//上(0)、右(1)、下(2)、左(3)的行偏移
    {0,-1,0,1}
}, num[1010][1010], tot, ans;//网格值 总计数 答案
bool vis[1002][1002][4];//访问状态[行][列][方向]

void dfs(const int x, const int y, const int d, const int len) {//坐标(x,y)，方向d，路径长度len
    bool mark = false;//是否进行了扩展
    for (int i = 0; i < 4; ++i) {
        if (num[x+dir[0][i]][y+dir[1][i]] == 0 ||//相邻位置值为0
            vis[x][y][i] == true) continue;
        vis[x][y][i] = true;
        vis[x+dir[0][i]][y+dir[1][i]][(i+2)%4] = true;//标记反方向已访问（防止回头）
        tot -= 2;//消除一对边
        if (d != -1 && i != d)//已有方向且新方向不同
            ans = __gcd(ans, len), dfs(x+dir[0][i], y+dir[1][i], i, 1);//长度重置为1
        else
            dfs(x+dir[0][i], y+dir[1][i], i, len+1);
        mark = true;//标记进行了扩展
    }
    if (mark == false) ans = __gcd(ans, len);//如果没有扩展，更新GCD
}


int main() {
    fast;
    int n, m, i, j, k; cin >> n >> m;
    memset(num, 0, sizeof(num));
    for (i = 1; i <= n; ++i) for (j = 1; j <= m; ++j) {
        cin >> num[i][j];//读取位置(i,j)的值
    }
    int od = 0; ans = 0; tot = 0;
    for (i = 1; i <= n; ++i) for (j = 1; j <= m; ++j) {
        if (num[i][j] == 0) continue;//当前位置为空
        for (ans = 0, k = 0; k < 4; ++k)//当前位置周围相邻值的和
            ans += num[i+dir[0][k]][j+dir[1][k]];//累加四个方向的邻居值
        tot += ans;//累加到总数
        if (ans == 0) return cout << "-1\n", 0;
        if (ans&1) od++;
    }
    if (od != 0 && od != 2) return cout << "-1\n", 0;//奇数邻居和的个数不是0或2，无解
    memset(vis, 0, sizeof(vis));
    ans = 0;
    for (i = 1; i <= n; ++i) for (j = 1; j <= m; ++j) if (num[i][j]) {//找到第一个非零位置
        dfs(i, j, -1, 0);
        goto A;
    }
    A:;
    if (tot || ans <= 1) return cout << "-1\n", 0;//仍有未处理元素或答案≤1，无解
    for (i = 2; i < ans; ++i) if (ans % i == 0) cout << i << ' ';//输出ans的所有因数
    cout << ans << '\n';//输出ans本身
    return 0;
}