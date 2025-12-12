//
// Created by Psy.C on 2025/12/13.
//
/*
*mp[N][N]定义二维矩阵，用于存储数字
num[N]数组存储每行的列数
*a[N*10]数组记录每个数字当前所在的位置(x,y坐标)
b[N*10]数组记录交换操作的信息
 *
*s表示当前应该放置的正确数字(从1开始)
ans记录交换操作次数
双重循环遍历整个矩阵：
如果当前位置(i,j)的数字不是s：
记录交换信息到b[ans]
获取当前位置的数字t
交换当前位置和数字s所在位置的值
更新位置记录数组a中相关数字的坐标信息
增加s和ans
否则只增加s
 *
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1010
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;


int main() {
    fast;
    int n; cin>>n;
    int mp[N][N] = {}, num[N];
    rep(i,n) cin>>num[i];
    struct node { int x, y, x1, y2; } a[N*10], b[N*10];
    rep(i,n) rep(j,num[i]) {
        cin>>mp[i][j];
        a[mp[i][j]].x = i; a[mp[i][j]].y = j;
    }
    int s = 1, ans = 0;
    rep(i,n) rep(j,num[i]) {
        if (mp[i][j] != s) {
            b[ans].x = i, b[ans].y = j;
            b[ans].x1 = a[s].x, b[ans].y2 = a[s].y;
            const int t = mp[i][j];
            swap(mp[i][j], mp[a[s].x][a[s].y]);
            const int t1 = a[s].x, t2 = a[s].y;
            a[s].x = i, a[s].y = j;
            a[t].x = t1, a[t].y = t2;
            s++; ans++;
        } else s++;
    }
    cout << ans << '\n';
    for (int i = 0; i < ans; ++i) cout << b[i].x << ' ' <<
        b[i].y << ' ' << b[i].x1 << ' ' << b[i].y2 << '\n';//交换前位置和交换后位置
    return 0;
}